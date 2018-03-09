#include "node2/CompMask.h"
#include "node2/AABBHelper.h"

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

void CompMask::Traverse(std::function<bool(const n0::SceneNodePtr&)> func) const
{
	if (m_base) {
		func(m_base);
	}
	if (m_mask) {
		func(m_mask);
	}
}

sm::rect CompMask::GetBounding() const
{
	sm::rect aabb;
	if (m_mask) {
		AABBHelper::Combine(aabb, m_mask);
	}
	return aabb;
}

void CompMask::InitNodeCount() const
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
	m_node_count = count;
}

}