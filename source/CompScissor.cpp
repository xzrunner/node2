#include "node2/CompScissor.h"

namespace n2
{

const char* const CompScissor::TYPE_NAME = "n2_scissor";

std::unique_ptr<n0::NodeUniqueComp> CompScissor::Clone(const n0::SceneNode& node) const
{
	auto comp = std::make_unique<CompScissor>();
	comp->m_rect = m_rect;
	return comp;
}

}