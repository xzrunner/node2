#include "node2/UpdateSystem.h"
#include "node2/CompAnim.h"
#include "node2/CompAnimInst.h"
#include "node2/CompParticle3d.h"
#include "node2/CompParticle3dInst.h"

#include <node0/SceneNode.h>

namespace n2
{

bool UpdateSystem::Update(const n0::SceneNodePtr& node)
{
	if (!node) {
		return false;
	}

	bool dirty = false;

	auto& casset = node->GetSharedComp<n0::CompAsset>();
	auto asset_type = casset.AssetTypeID();
	if (asset_type == n0::GetAssetUniqueTypeID<n2::CompAnim>())
	{
		auto& canim = node->GetUniqueComp<n2::CompAnimInst>();
		if (canim.Update()) {
			dirty = true;
		}
	}
	else if (asset_type == n0::GetAssetUniqueTypeID<n2::CompParticle3d>())
	{
		auto& cp3d = node->GetUniqueComp<n2::CompParticle3dInst>();
		if (cp3d.Update()) {
			dirty = true;
		}
	}

	return dirty;
}

}