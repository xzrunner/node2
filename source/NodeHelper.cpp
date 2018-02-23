#include "node2/NodeHelper.h"
#include "node2/CompBoundingBox.h"
#include "node2/CompTransform.h"

#include <node0/SceneNode.h>

namespace n2
{

void NodeHelper::SetBoundingSize(n0::SceneNode& node, const sm::rect& sz)
{
	if (!node.HasComponent<CompBoundingBox>()) {
		return;
	}

	auto& cbounding = node.GetComponent<CompBoundingBox>();
	cbounding.SetSize(sz);

	if (node.HasComponent<CompTransform>()) {
		cbounding.Build(node.GetComponent<CompTransform>().GetTrans().GetSRT());
	} else {
		cbounding.Build(pt2::SRT());
	}
}

}