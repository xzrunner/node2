#include "node2/CompMask.h"

namespace n2
{

const char* const CompMask::TYPE_NAME = "n2_mask";

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