#include "node2/UpdateSystem.h"
#include "node2/CompAnim.h"
#include "node2/CompAnimInst.h"
#include "node2/CompParticle3d.h"
#include "node2/CompParticle3dInst.h"
#include "node2/CompScript.h"

#include <node0/SceneNode.h>

namespace n2
{

CU_SINGLETON_DEFINITION(UpdateSystem);

UpdateSystem::UpdateSystem()
{
}

bool UpdateSystem::Update(const n0::SceneNodePtr& node)
{
	if (!node) {
		return false;
	}

	bool dirty = false;

	if (node->HasSharedComp<n0::CompAsset>())
	{
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
	}

	// script
	if (node->HasUniqueComp<n2::CompScript>())
	{
		auto& cscript = node->GetUniqueComp<n2::CompScript>();
		cscript.GetImpl().Update();
	}

	// ext comp
	for (auto& func : m_update_comp_funcs) {
		if (func(*node)) {
			dirty = true;
		}
	}

	return dirty;
}

void UpdateSystem::AddUpdateCompFunc(std::function<bool(const n0::SceneNode&)> func)
{
	m_update_comp_funcs.push_back(func);
}

}