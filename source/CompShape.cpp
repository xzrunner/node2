#include "node2/CompShape.h"

#include <guard/check.h>
#include <geoshape/Shape.h>

namespace n2
{

const char* const CompShape::TYPE_NAME = "n2_shape";

CompShape::CompShape(const std::shared_ptr<gs::Shape>& shape)
	: m_shape(shape)
{
}

std::unique_ptr<n0::NodeComp> CompShape::Clone(const n0::SceneNode& node) const
{
	return std::make_unique<CompShape>(m_shape->Clone());
}

}