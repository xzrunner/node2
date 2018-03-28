#include "node2/UpdateSystem.h"
#include "node2/CompAnim.h"

#include <node0/SceneNode.h>

namespace n2
{

bool UpdateSystem::Update(const n0::SceneNodePtr& node)
{
	if (!node) {
		return false;
	}

	bool dirty = false;

	if (node->HasSharedComp<CompAnim>())
	{
		auto& canim = node->GetSharedComp<CompAnim>();
		if (canim.GetPlayCtrl().Update()) {
			dirty = true;
		}
	}

	return dirty;
}

}