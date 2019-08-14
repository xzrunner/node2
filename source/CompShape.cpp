#include "node2/CompShape.h"

#include <guard/check.h>
#include <geoshape/Shape2D.h>

namespace n2
{

const char* const CompShape::TYPE_NAME = "n2_shape";

CompShape::CompShape(const std::shared_ptr<gs::Shape2D>& shape)
	: m_shape(shape)
{
}

}