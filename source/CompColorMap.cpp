#include "node2/CompColorMap.h"

namespace n2
{

const char* const CompColorMap::TYPE_NAME = "n2_color_map";

std::unique_ptr<n0::NodeComp> CompColorMap::Clone(const n0::SceneNode& node) const
{
	auto comp = std::make_unique<CompColorMap>();
	comp->m_col = m_col;
	return comp;
}

}