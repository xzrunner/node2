#include "node2/SceneTreeHelper.h"
#include "node2/CompBoundingBox.h"
#include "node2/AABBHelper.h"
#include "node2/CompTransform.h"

#include <node0/SceneNode.h>
#include <node0/CompAsset.h>
#include <node0/SceneTreeHelper.h>
#include <painting2/BoundingBox.h>

namespace n2
{

void SceneTreeHelper::UpdateAABB(const n0::SceneNodePtr& node, 
	                             const n0::SceneNodePtr& root, 
	                             size_t node_id)
{
	sm::rect new_aabb;
	AABBHelper::Combine(new_aabb, node);
	auto& cbb = node->GetUniqueComp<CompBoundingBox>();
	if (cbb.GetBounding(*node).GetSize() == new_aabb) {
		return;
	}

	std::vector<n0::SceneNodePtr> path;
	n0::SceneTreeHelper::GetPathToRoot(root, node_id, path);
	for (auto& itr = path.rbegin(); itr != path.rend(); ++itr)
	{
		auto& node = *itr;

		sm::rect new_aabb;
		AABBHelper::Combine(new_aabb, node);
		auto& cbb = node->GetUniqueComp<CompBoundingBox>();
		if (cbb.GetBounding(*node).GetSize() == new_aabb) {
			break;
		}

		auto& ctrans = node->GetUniqueComp<CompTransform>();
		new_aabb.Translate(-ctrans.GetTrans().GetPosition());
		cbb.SetSize(*node, new_aabb);
	}
}

}