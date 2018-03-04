#include "node2/CompMask.h"

#include <node0/SceneNode.h>

namespace n2
{

const char* const CompMask::TYPE_NAME = "n2_mask";

std::unique_ptr<n0::NodeComponent> CompMask::Clone() const
{
	auto comp = std::make_unique<CompMask>();
	comp->m_base = m_base->Clone();
	comp->m_mask = m_mask->Clone();
	return comp;
}

void CompMask::Traverse(std::function<bool(const n0::SceneNodePtr&)> func) const
{
	if (m_base) {
		func(m_base);
	}
	if (m_mask) {
		func(m_mask);
	}
}

}