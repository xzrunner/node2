#include "node2/CompBoundingBox.h"

#include <guard/check.h>
#include <painting2/OBB.h>
#include <painting2/SRT.h>

namespace n2
{

const char* const CompBoundingBox::TYPE_NAME = "n2_bounding_box";

std::unique_ptr<n0::NodeUniqueComp> CompBoundingBox::Clone() const
{
	auto comp = std::make_unique<CompBoundingBox>();
	comp->m_size = m_size;
	comp->m_bounding = m_bounding->Clone2();
	return comp;
}

void CompBoundingBox::SetSize(const sm::rect& size)
{
	m_size = size;
}

void CompBoundingBox::Build(const pt2::SRT& srt)
{
	m_bounding = std::make_unique<pt2::OBB>();
	m_bounding->Build(m_size, srt.position, srt.angle, srt.scale, srt.shear, srt.offset);
}

const pt2::BoundingBox& CompBoundingBox::GetBounding() const
{
	GD_ASSERT(m_bounding, "null bounding");
	return *m_bounding;
}

}