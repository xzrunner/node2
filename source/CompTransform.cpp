#include "node2/CompTransform.h"

namespace n2
{

const char* const CompTransform::TYPE_NAME = "n2_transform";

std::unique_ptr<n0::NodeUniqueComp> CompTransform::Clone() const
{
	auto comp = std::make_unique<CompTransform>();
	comp->m_transform = m_transform;
	return comp;
}

}