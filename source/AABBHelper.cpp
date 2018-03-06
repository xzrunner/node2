#include "node2/AABBHelper.h"
#include "node2/CompTransform.h"

#include <node0/SceneNode.h>
#include <node0/CompAsset.h>

namespace n2
{

void AABBHelper::Combine(sm::rect& aabb, const n0::SceneNodePtr& child)
{
	auto& casset = child->GetSharedComp<n0::CompAsset>();
	auto c_aabb = casset.GetBounding();
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

}