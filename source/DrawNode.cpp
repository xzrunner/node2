#include "node2/DrawNode.h"
#include "node2/CompTransform.h"
#include "node2/CompImage.h"
#include "node2/CompColorCommon.h"
#include "node2/CompColorMap.h"
#include "node2/CompText.h"
#include "node2/CompMask.h"
#include "node2/CompSprite2.h"

#include <node0/SceneNode.h>
#include <painting2/RenderSystem.h>
#include <painting2/DrawMask.h>
#include <sprite2/DrawNode.h>

namespace n2
{

void DrawNode::Draw(const n0::SceneNodePtr& node, const N2_MAT& mt)
{
	auto& ctrans = node->GetComponent<CompTransform>();
	auto mt_child = ctrans.GetTrans().GetMatrix() * mt;

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
		pt2::DrawMask::Draw(cmask.GetBaseNode(), cmask.GetMaskNode(), sm::Matrix2D(), 
			[&](const n0::SceneNodePtr& node, const sm::Matrix2D& mat)
			{
				Draw(node, mat);
			}
		);
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
}

}