#include "node2/CompMask.h"
#include "node2/AABBSystem.h"

#include <node0/SceneNode.h>

namespace n2
{

const char* const CompMask::TYPE_NAME = "n2_mask";

//std::unique_ptr<n0::NodeComponent> CompMask::Clone() const
//{
//	auto comp = std::make_unique<CompMask>();
//	comp->m_base = m_base->Clone();
//	comp->m_mask = m_mask->Clone();
//	return comp;
//}

void CompMask::Traverse(std::function<bool(const n0::SceneNodePtr&)> func, bool inverse) const
{
	if (m_base) {
		if (!func(m_base)) {
			return;
		}
	}
	if (m_mask) {
		if (!func(m_mask)) {
			return;
		}
	}
}

void CompMask::SetBaseNode(const n0::SceneNodePtr& base)
{
	m_base = base;
	m_node_count = CalcNodeCount();
}

void CompMask::SetMaskNode(const n0::SceneNodePtr& mask)
{
	m_mask = mask;
	m_node_count = CalcNodeCount();
}

int CompMask::CalcNodeCount() const
{
	size_t count = 1;
	if (m_base)
	{
		auto& casset = m_base->GetSharedComp<n0::CompAsset>();
		count += casset.GetNodeCount();
	}
	if (m_mask)
	{
		auto& casset = m_mask->GetSharedComp<n0::CompAsset>();
		count += casset.GetNodeCount();
	}
	return count;
}

}