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

#include <node0/SceneNode.h>
#include <node0/CompComplex.h>
#include <painting2/RenderSystem.h>
#include <painting2/DrawMask.h>
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
		return n2::RenderSystem::Draw(node, sm::Matrix2D());
	}
	virtual pt2::RenderReturn DrawMaskNode(const n0::SceneNodePtr& node, const sm::Matrix2D& mt) const override
	{
		return n2::RenderSystem::Draw(node, sm::Matrix2D());
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

pt2::RenderReturn RenderSystem::Draw(const n0::SceneNodePtr& node, const N2_MAT& mt)
{
	if (!node) {
		return pt2::RENDER_NO_DATA;
	}

	pt2::RenderReturn ret = pt2::RENDER_OK;

	auto mt_child = mt;
	if (node->HasUniqueComp<CompTransform>())
	{
		auto& ctrans = node->GetUniqueComp<CompTransform>();
		mt_child = ctrans.GetTrans().GetMatrix() * mt;
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
		auto& cscale9 = node->GetSharedComp<CompScale9>();
		cscale9.Traverse([&](const n0::SceneNodePtr& node)->bool {
			RenderSystem::Draw(node, mt_child);
			return true;
		});
	}

	if (node->HasSharedComp<CompSprite2>())
	{
		auto& csprite2 = node->GetSharedComp<CompSprite2>();
		auto& sym = csprite2.GetSymbol();
		s2::DrawNode::Draw(*sym, s2::RenderParams(), mt_child);
	}
	
	if (node->HasSharedComp<n0::CompComplex>())
	{
		auto& ccomplex = node->GetSharedComp<n0::CompComplex>();
		auto& children = ccomplex.GetAllChildren();
		for (auto& child : children) {
			Draw(child, mt_child);
		}
	}

	return ret;
}

}