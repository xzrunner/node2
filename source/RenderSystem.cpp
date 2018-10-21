#include "node2/RenderSystem.h"
#include "node2/CompTransform.h"
#include "node2/CompImage.h"
#include "node2/CompColorCommon.h"
#include "node2/CompColorMap.h"
#include "node2/CompText.h"
#include "node2/CompMask.h"
#include "node2/CompBoundingBox.h"
#include "node2/CompScale9.h"
#include "node2/CompAnim.h"
#include "node2/CompAnimInst.h"
#include "node2/CompParticle3d.h"
#include "node2/CompParticle3dInst.h"
#include "node2/CompUniquePatch.h"
#include "node2/CompScissor.h"
#include "node2/CompScript.h"
#include "node2/CompShape.h"
#include "node2/EditOp.h"

#include <node0/SceneNode.h>
#include <node0/CompComplex.h>
#include <painting2/RenderSystem.h>
#include <painting2/DrawMask.h>
#include <painting2/PrimitiveDraw.h>
#include <anim/Layer.h>
#include <anim/KeyFrame.h>
#include <tessellation/Painter.h>

namespace
{

class DrawMask : public pt2::DrawMask<n0::SceneNodePtr, sm::Matrix2D>
{
public:
	DrawMask(const n0::SceneNodePtr& base, const n0::SceneNodePtr& mask, const sm::Matrix2D& mt)
		: pt2::DrawMask<n0::SceneNodePtr, sm::Matrix2D>(base, mask, mt) {}

	virtual pt2::RenderReturn Draw(cooking::DisplayList* dlist) const override
	{
		if (!m_base || !m_mask) {
			return pt2::RENDER_NO_DATA;
		}
		return this->DrawImpl(dlist);
	}

protected:
	virtual pt2::RenderReturn DrawBaseNode(const n0::SceneNodePtr& node, const sm::Matrix2D& mt) const override
	{
		return n2::RenderSystem::Instance()->Draw(node);
	}
	virtual pt2::RenderReturn DrawMaskNode(const n0::SceneNodePtr& node, const sm::Matrix2D& mt) const override
	{
		return n2::RenderSystem::Instance()->Draw(node);
	}

	virtual sm::rect GetBounding(const n0::SceneNodePtr& node) const override
	{
		auto& bb = node->GetUniqueComp<n2::CompBoundingBox>();
		return bb.GetSize();
	}

	const sm::Matrix2D& GetMat(const sm::Matrix2D& mt) const override
	{
		return mt;
	}

}; // DrawMask

}

namespace n2
{

CU_SINGLETON_DEFINITION(RenderSystem);

RenderSystem::RenderSystem()
{
}

pt2::RenderReturn RenderSystem::Draw(const n0::SceneNodePtr& node,
	                                 const RenderParams& rp)
{
	if (!node) {
		return pt2::RENDER_NO_DATA;
	}

	if (rp.patch) {
		rp.patch->Seek(rp.node_id);
	}

	pt2::RenderReturn ret = pt2::RENDER_OK;

	RenderParams rp_child(rp);

	// matrix
	if (node->HasUniqueComp<CompTransform>())
	{
		auto& ctrans = node->GetUniqueComp<CompTransform>();
		rp_child.mt = ctrans.GetTrans().GetMatrix() * rp.mt;
	}
	if (rp.patch && rp.patch->HasEditOp(rp.node_id)) {
		auto& op_list = rp.patch->GetEditOp(rp.node_id);
		if (op_list.HasEditOp(EditOpID::SetTransformMatOp)) {
			auto& op = static_cast<const SetTransformMatOp&>(op_list.GetEditOp(EditOpID::SetTransformMatOp));
			rp_child.mt = op.mat * rp.mt;
		}
	}

	// begin scissor
	if (!rp.is_edit_mode && node->HasUniqueComp<n2::CompScissor>())
	{
		auto& cscissor = node->GetUniqueComp<n2::CompScissor>();
		auto& rect = cscissor.GetRect();
		auto min = rp_child.mt * sm::vec2(rect.xmin, rect.ymin);
		auto max = rp_child.mt * sm::vec2(rect.xmax, rect.ymax);
		if (min.x > max.x) {
			std::swap(min.x, max.x);
		}
		if (min.y > max.y) {
			std::swap(min.y, max.y);
		}
		auto& pt2_rc = pt2::Blackboard::Instance()->GetRenderContext();
		pt2_rc.GetScissor().Push(min.x, min.y, max.x - min.x, max.y - min.y, true, false);
	}

	// color
	if (node->HasUniqueComp<CompColorCommon>())
	{
		auto& ccol = node->GetUniqueComp<CompColorCommon>();
		pt2::RenderSystem::SetColor(rp.GetColor() * ccol.GetColor());
	}
	else
	{
		pt2::RenderSystem::SetColor(rp.GetColor());
	}
	if (node->HasUniqueComp<CompColorMap>())
	{
		auto& ccol = node->GetUniqueComp<CompColorMap>();
		pt2::RenderSystem::SetColorMap(ccol.GetColor());
	}

	// ext comp
	for (auto& func : m_draw_comp_funcs) {
		func(*node, rp_child);
	}

	// asset
	if (node->HasSharedComp<n0::CompAsset>())
	{
		auto& casset = node->GetSharedComp<n0::CompAsset>();
		ret |= DrawAsset(casset, rp_child);
		auto asset_type = casset.AssetTypeID();
		if (asset_type == n0::GetAssetUniqueTypeID<n2::CompAnim>())
		{
			rp_child.node_id += 1;

			auto& canim_inst = node->GetUniqueComp<n2::CompAnimInst>();
			canim_inst.TraverseCurrNodes([&](const n0::SceneNodePtr& node)->bool
			{
				Draw(node, rp_child);
				return true;
			});
		}
		else if (asset_type == n0::GetAssetUniqueTypeID<n2::CompParticle3d>())
		{
			rp_child.node_id += 1;

			auto& cp3d_inst = node->GetUniqueComp<n2::CompParticle3dInst>();
			cp3d_inst.Draw(rp_child);
		}
	}

	// shape
	if (node->HasUniqueComp<n2::CompShape>())
	{
		auto& cshape = node->GetUniqueComp<n2::CompShape>();
		auto& shape = cshape.GetShape();
		assert(shape);

		uint32_t color = 0;
		if (node->HasUniqueComp<CompColorCommon>())
		{
			auto& ccol = node->GetUniqueComp<CompColorCommon>();
			color = (rp.GetColor() * ccol.GetColor()).mul.ToABGR();
		}
		else
		{
			color = rp.GetColor().mul.ToABGR();
		}

		auto src = rp_child.mt.x;
		sm::mat4 dst;
		dst.x[0]  = src[0];
		dst.x[1]  = src[1];
		dst.x[4]  = src[2];
		dst.x[5]  = src[3];
		dst.x[12] = src[4];
		dst.x[13] = src[5];
		tess::Painter pt;
		pt2::RenderSystem::DrawShape(pt, *shape, color);
		pt2::RenderSystem::DrawPainter(pt, dst);
	}

	// script
	if (node->HasUniqueComp<n2::CompScript>())
	{
		auto& cscript = node->GetUniqueComp<n2::CompScript>();
		cscript.GetImpl().Draw();
	}

	// end scissor
	if (node->HasUniqueComp<n2::CompScissor>())
	{
		if (rp.is_edit_mode)
		{
			auto& cscissor = node->GetUniqueComp<n2::CompScissor>();
			DrawScissorRect(cscissor.GetRect(), rp_child.mt);
		}
		else
		{
			auto& pt2_rc = pt2::Blackboard::Instance()->GetRenderContext();
			pt2_rc.GetScissor().Pop();
		}
	}

	return ret;
}

pt2::RenderReturn RenderSystem::Draw(const n0::CompAsset& casset,
	                                 const sm::vec2& pos,
	                                 float angle,
	                                 const sm::vec2& scale,
	                                 const sm::vec2& shear,
	                                 const RenderParams& rp)
{
	sm::Matrix2D mat;
	mat.SetTransformation(pos.x, pos.y, angle, scale.x, scale.y, 0, 0, shear.x, shear.y);
	mat = mat * rp.mt;

	RenderParams rp_child(rp);
	rp_child.mt = mat;

	pt2::RenderSystem::SetColor(rp.GetColor());

	return DrawAsset(casset, rp_child);
}

pt2::RenderReturn RenderSystem::Draw(const n0::CompAsset& casset, const sm::Matrix2D& mat)
{
	RenderParams rp;
	rp.mt = mat;

	pt2::RenderSystem::SetColor(rp.GetColor());

	return DrawAsset(casset, rp);
}

void RenderSystem::DrawScissorRect(const sm::rect& rect, const N2_MAT& mt)
{
	pt2::PrimitiveDraw::SetColor(pt2::Color(0, 204, 0));
	pt2::PrimitiveDraw::LineWidth(2);
	auto min = mt * sm::vec2(rect.xmin, rect.ymin);
	auto max = mt * sm::vec2(rect.xmax, rect.ymax);
	pt2::PrimitiveDraw::Rect(nullptr, min, max, false);
}

void RenderSystem::AddDrawAssetFunc(n0::AssetID id, std::function<void(const n0::CompAsset&, const n2::RenderParams&)> func)
{
	if (id >= m_draw_asset_funcs.size()) {
		m_draw_asset_funcs.resize(id + 1);
	}
	m_draw_asset_funcs[id] = func;
}

void RenderSystem::AddDrawCompFunc(std::function<void(const n0::SceneNode&, const n2::RenderParams&)> func)
{
	m_draw_comp_funcs.push_back(func);
}

pt2::RenderReturn RenderSystem::DrawAsset(const n0::CompAsset& casset, RenderParams& rp)
{
	pt2::RenderReturn ret = pt2::RENDER_OK;
	auto asset_type = casset.AssetTypeID();
	if (asset_type == n0::GetAssetUniqueTypeID<n2::CompImage>())
	{
		auto& cimage = static_cast<const n2::CompImage&>(casset);
		auto& tex = cimage.GetTexture();
		if (tex)
		{
			auto sz = tex->GetSize();
			if (rp.m_quad_base_left_top)
			{
				sm::rect r;
				r.xmin = 0; r.xmax = sz.x;
				r.ymin = -sz.y; r.ymax = 0;
				pt2::RenderSystem::DrawTexture(*tex, r, rp.mt);
			}
			else
			{
				pt2::RenderSystem::DrawTexture(*tex, sm::rect(sz.x, sz.y), rp.mt);
			}
		}
	}
	else if (asset_type == n0::GetAssetUniqueTypeID<n2::CompText>())
	{
		auto& ctext = static_cast<const CompText&>(casset);
		auto& text = ctext.GetText();
		auto& col = rp.GetColor();
		pt2::RenderSystem::DrawText(text.text, text.tb, rp.mt, col.mul, col.add);
	}
	else if (asset_type == n0::GetAssetUniqueTypeID<n2::CompMask>())
	{
		auto& cmask = static_cast<const CompMask&>(casset);
		DrawMask draw(cmask.GetBaseNode(), cmask.GetMaskNode(), rp.mt);
		ret |= draw.Draw(nullptr);
	}
	else if (asset_type == n0::GetAssetUniqueTypeID<n2::CompScale9>())
	{
		auto& cscale9 = static_cast<const CompScale9&>(casset);
		cscale9.Traverse([&](const n0::SceneNodePtr& node)->bool {
			RenderSystem::Draw(node, rp);
			return true;
		});
	}
	else if (asset_type == n0::GetAssetUniqueTypeID<n0::CompComplex>())
	{
		auto& ccomplex = static_cast<const n0::CompComplex&>(casset);
		auto& children = ccomplex.GetAllChildren();
		if (!children.empty())
		{
			rp.node_id += 1;

			for (auto& child : children)
			{
				Draw(child, rp);
				auto& casset = child->GetSharedComp<n0::CompAsset>();
				rp.node_id += casset.GetNodeCount();
			}
		}
	}
	else
	{
		if (asset_type < m_draw_asset_funcs.size() &&
			m_draw_asset_funcs[asset_type]) {
			m_draw_asset_funcs[asset_type](casset, rp);
		}
	}

	return ret;
}

}