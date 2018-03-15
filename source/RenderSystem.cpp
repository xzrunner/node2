#include "node2/RenderSystem.h"
#include "node2/CompTransform.h"
#include "node2/CompImage.h"
#include "node2/CompColorCommon.h"
#include "node2/CompColorMap.h"
#include "node2/CompText.h"
#include "node2/CompMask.h"
#include "node2/CompSprite2.h"
#include "node2/CompBoundingBox.h"
#include "node2/CompScale9.h"
#include "node2/CompComplex.h"
#include "node2/CompUniquePatch.h"
#include "node2/CompScissor.h"
#include "node2/EditOp.h"

#include <node0/SceneNode.h>
#include <painting2/RenderSystem.h>
#include <painting2/DrawMask.h>
#include <painting2/PrimitiveDraw.h>
#include <sprite2/DrawNode.h>

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
		return n2::RenderSystem::Draw(node);
	}
	virtual pt2::RenderReturn DrawMaskNode(const n0::SceneNodePtr& node, const sm::Matrix2D& mt) const override
	{
		return n2::RenderSystem::Draw(node);
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

	// matrix
	auto mt_child = rp.mt;
	if (node->HasUniqueComp<CompTransform>())
	{
		auto& ctrans = node->GetUniqueComp<CompTransform>();
		mt_child = ctrans.GetTrans().GetMatrix() * rp.mt;
	}
	if (rp.patch && rp.patch->HasEditOp(rp.node_id)) {
		auto& op_list = rp.patch->GetEditOp(rp.node_id);
		if (op_list.HasEditOp(EditOpID::SetTransformMatOp)) {
			auto& op = static_cast<const SetTransformMatOp&>(op_list.GetEditOp(EditOpID::SetTransformMatOp));
			mt_child = op.mat * rp.mt;
		}
	}

	// begin scissor
	if (!rp.is_edit_mode && node->HasUniqueComp<n2::CompScissor>())
	{
		auto& cscissor = node->GetUniqueComp<n2::CompScissor>();
		auto& rect = cscissor.GetRect();
		auto min = mt_child * sm::vec2(rect.xmin, rect.ymin);
		auto max = mt_child * sm::vec2(rect.xmax, rect.ymax);
		if (min.x > max.x) {
			std::swap(min.x, max.x);
		}
		if (min.y > max.y) {
			std::swap(min.y, max.y);
		}
		auto& pt2_rc = pt2::Blackboard::Instance()->GetRenderContext();
		pt2_rc.GetScissor().Push(min.x, min.y, max.x - min.x, max.y - min.y, true, false);
	}

	if (node->HasUniqueComp<CompColorCommon>())
	{
		auto& ccol = node->GetUniqueComp<CompColorCommon>();
		pt2::RenderSystem::SetColor(ccol.GetColor());
	}
	if (node->HasUniqueComp<CompColorMap>())
	{
		auto& ccol = node->GetUniqueComp<CompColorMap>();
		pt2::RenderSystem::SetColorMap(ccol.GetColor());
	}

	if (node->HasSharedComp<CompImage>())
	{
		auto& cimage = node->GetSharedComp<CompImage>();
		auto& tex = cimage.GetTexture();
		if (tex) {
			auto sz = tex->GetSize();
			pt2::RenderSystem::DrawTexture(*tex, sm::rect(sz.x, sz.y), mt_child);
		}
	}
	if (node->HasSharedComp<CompText>())
	{
		auto& ctext = node->GetSharedComp<CompText>();
		auto& text = ctext.GetText();
		pt2::RenderSystem::DrawText(text, mt_child);
	}
	if (node->HasSharedComp<CompMask>())
	{
		auto& cmask = node->GetSharedComp<CompMask>();
		DrawMask draw(cmask.GetBaseNode(), cmask.GetMaskNode(), mt_child);
		ret |= draw.Draw(nullptr);
	}
	if (node->HasSharedComp<CompScale9>())
	{
		RenderParams rp_child(rp);
		rp_child.mt = mt_child;

		auto& cscale9 = node->GetSharedComp<CompScale9>();
		cscale9.Traverse([&](const n0::SceneNodePtr& node)->bool {
			RenderSystem::Draw(node, rp_child);
			return true;
		});
	}

	if (node->HasSharedComp<CompSprite2>())
	{
		auto& csprite2 = node->GetSharedComp<CompSprite2>();
		auto& sym = csprite2.GetSymbol();
		s2::DrawNode::Draw(*sym, s2::RenderParams(), mt_child);
	}
	
	if (node->HasSharedComp<n2::CompComplex>())
	{
		auto& ccomplex = node->GetSharedComp<n2::CompComplex>();
		auto& children = ccomplex.GetAllChildren();
		if (!children.empty())
		{
			RenderParams rp_child(rp);
			rp_child.mt = mt_child;
			rp_child.node_id += 1;

			for (auto& child : children)
			{
				Draw(child, rp_child);
				auto& casset = child->GetSharedComp<n0::CompAsset>();
				rp_child.node_id += casset.GetNodeCount();
			}
		}
	}

	// end scissor
	if (node->HasUniqueComp<n2::CompScissor>())
	{
		if (rp.is_edit_mode)
		{
			auto& cscissor = node->GetUniqueComp<n2::CompScissor>();
			DrawScissorRect(cscissor.GetRect(), mt_child);
		}
		else
		{
			auto& pt2_rc = pt2::Blackboard::Instance()->GetRenderContext();
			pt2_rc.GetScissor().Pop();
		}
	}

	return ret;
}

void RenderSystem::DrawScissorRect(const sm::rect& rect, const N2_MAT& mt)
{
	pt2::PrimitiveDraw::SetColor(pt2::Color(0, 204, 0));
	pt2::PrimitiveDraw::LineWidth(2);
	auto min = mt * sm::vec2(rect.xmin, rect.ymin);
	auto max = mt * sm::vec2(rect.xmax, rect.ymax);
	pt2::PrimitiveDraw::Rect(nullptr, min, max, false);
}

}