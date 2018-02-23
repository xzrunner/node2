#include "node2/DrawNode.h"
#include "node2/CompTransform.h"
#include "node2/CompImage.h"
#include "node2/CompColorCommon.h"
#include "node2/CompColorMap.h"
#include "node2/CompText.h"
#include "node2/CompMask.h"
#include "node2/CompSprite2.h"
#include "node2/CompBoundingBox.h"

#include <node0/SceneNode.h>
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
		return n2::DrawNode::Draw(node, mt);
	}
	virtual pt2::RenderReturn DrawMaskNode(const n0::SceneNodePtr& node, const sm::Matrix2D& mt) const override
	{
		return n2::DrawNode::Draw(node, mt);
	}

	virtual sm::rect GetBounding(const n0::SceneNodePtr& node) const override
	{
		auto& bb = node->GetComponent<n2::CompBoundingBox>();
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

pt2::RenderReturn DrawNode::Draw(const n0::SceneNodePtr& node, const N2_MAT& mt)
{
	pt2::RenderReturn ret = pt2::RENDER_OK;

	auto mt_child = mt;
	if (node->HasComponent<CompTransform>())
	{
		auto& ctrans = node->GetComponent<CompTransform>();
		mt_child = ctrans.GetTrans().GetMatrix() * mt;
	}

	if (node->HasComponent<CompColorCommon>())
	{
		auto& ccol = node->GetComponent<CompColorCommon>();
		pt2::RenderSystem::SetColor(ccol.GetColor());
	}
	if (node->HasComponent<CompColorMap>())
	{
		auto& ccol = node->GetComponent<CompColorMap>();
		pt2::RenderSystem::SetColorMap(ccol.GetColor());
	}

	if (node->HasComponent<CompImage>())
	{
		auto& cimage = node->GetComponent<CompImage>();
		auto& tex = cimage.GetTexture();
		if (tex) {
			auto sz = tex->GetSize();
			pt2::RenderSystem::DrawTexture(*tex, sm::rect(sz.x, sz.y), mt_child);
		}
	}
	if (node->HasComponent<CompText>())
	{
		auto& ctext = node->GetComponent<CompText>();
		auto& text = ctext.GetText();
		pt2::RenderSystem::DrawText(text, mt_child);
	}
	if (node->HasComponent<CompMask>())
	{
		auto& cmask = node->GetComponent<CompMask>();
		DrawMask draw(cmask.GetBaseNode(), cmask.GetMaskNode(), sm::Matrix2D());
		ret |= draw.Draw(nullptr);
	}

	if (node->HasComponent<CompSprite2>())
	{
		auto& csprite2 = node->GetComponent<CompSprite2>();
		auto& sym = csprite2.GetSymbol();
		s2::DrawNode::Draw(*sym, s2::RenderParams(), mt_child);
	}
	
	auto& children = node->GetAllChildren();
	for (auto& child : children) {
		Draw(child, mt_child);
	}

	return ret;
}

}