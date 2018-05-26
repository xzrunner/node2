#include "node2/CompColorCommon.h"

namespace n2
{

const char* const CompColorCommon::TYPE_NAME = "n2_color_common";

std::unique_ptr<n0::NodeComp> CompColorCommon::Clone(const n0::SceneNode& node) const
{
	auto comp = std::make_unique<CompColorCommon>();
	comp->m_col = m_col;
	return comp;
}

}