#include "node2/CompColorCommon.h"

namespace n2
{

const char* const CompColorCommon::TYPE_NAME = "n2_color_common";

std::unique_ptr<n0::NodeComponent> CompColorCommon::Clone() const
{
	auto comp = std::make_unique<CompColorCommon>();
	comp->m_col = m_col;
	return comp;
}

}