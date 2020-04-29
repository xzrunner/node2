#include "node2/AABBSystem.h"
#include "node2/CompTransform.h"

#include "node2/CompImage.h"
#include "node2/CompMask.h"
#include "node2/CompMesh.h"
#include "node2/CompAnim.h"
#include "node2/CompParticle3d.h"
#include "node2/CompScale9.h"
#include "node2/CompText.h"

#include <unirender/Texture.h>
#include <node0/SceneNode.h>
#include <node0/CompAsset.h>
#include <node0/CompComplex.h>
#include <anim/AnimTemplate.h>

namespace n2
{

CU_SINGLETON_DEFINITION(AABBSystem);

AABBSystem::AABBSystem()
{
}

sm::rect AABBSystem::GetBounding(const n0::CompAsset& casset)
{
	sm::rect rect;

	auto type = casset.AssetTypeID();
	if (type == n0::GetAssetUniqueTypeID<CompImage>())
	{
		auto& cimage = static_cast<const CompImage&>(casset);
		auto& tex = cimage.GetTexture();
		return sm::rect(
			static_cast<float>(tex->GetWidth()),
			static_cast<float>(tex->GetHeight())
		);
	}
	else if (type == n0::GetAssetUniqueTypeID<CompMask>())
	{
		auto& cmask = static_cast<const CompMask&>(casset);
		auto& mask = cmask.GetMaskNode();
		Combine(rect, mask);
	}
	else if (type == n0::GetAssetUniqueTypeID<CompMesh>())
	{
		rect = sm::rect(100, 100);
	}
	else if (type == n0::GetAssetUniqueTypeID<CompAnim>())
	{
		auto& canim = static_cast<const CompAnim&>(casset);
		auto& temp = canim.GetAnimTemplate();

		auto& slots = temp->GetAllSlots();
		for (auto& child : slots) {
			Combine(rect, child);
		}
	}
	else if (type == n0::GetAssetUniqueTypeID<CompParticle3d>())
	{
		rect = sm::rect(100, 100);
	}
	else if (type == n0::GetAssetUniqueTypeID<CompScale9>())
	{
		auto& cscale9 = static_cast<const CompScale9&>(casset);
		return sm::rect(cscale9.GetWidth(), cscale9.GetHeight());
	}
	else if (type == n0::GetAssetUniqueTypeID<CompText>())
	{
		rect = sm::rect(100, 100);
	}
	else if (type == n0::GetAssetUniqueTypeID<n0::CompComplex>())
	{
		auto& ccomplex = static_cast<const n0::CompComplex&>(casset);
		auto& children = ccomplex.GetAllChildren();
		for (auto& child : children) {
			Combine(rect, child);
		}
	}

	return rect;
}

void AABBSystem::Combine(sm::rect& aabb, const n0::SceneNodePtr& child)
{
	if (!child->HasSharedComp<n0::CompAsset>()) {
		return;
	}

	auto& casset = child->GetSharedComp<n0::CompAsset>();
	auto c_aabb = GetBounding(casset);
	if (!c_aabb.IsValid()) {
		return;
	}

	auto& ctrans = child->GetUniqueComp<CompTransform>();
	auto& mat = ctrans.GetTrans().GetMatrix();
	aabb.Combine(mat * sm::vec2(c_aabb.xmin, c_aabb.ymin));
	aabb.Combine(mat * sm::vec2(c_aabb.xmax, c_aabb.ymin));
	aabb.Combine(mat * sm::vec2(c_aabb.xmax, c_aabb.ymax));
	aabb.Combine(mat * sm::vec2(c_aabb.xmin, c_aabb.ymax));
}

sm::rect AABBSystem::GetBounding(const n0::SceneNode& node)
{
    if (node.HasSharedComp<n0::CompAsset>()) {
        auto aabb = GetBounding(node.GetSharedComp<n0::CompAsset>());
        if (aabb.IsValid()) {
            return aabb;
        }
    }

	for (auto& func : m_get_bound_funcs) {
		sm::rect bound;
		if (func(node, bound)) {
			return bound;
		}
	}
	return sm::rect();
}

void AABBSystem::AddGetBoundFunc(std::function<bool(const n0::SceneNode&, sm::rect& bound)> func)
{
	m_get_bound_funcs.push_back(func);
}

}