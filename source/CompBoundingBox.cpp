#include "node2/CompBoundingBox.h"
#include "node2/NodeFlags.h"
#include "node2/CompTransform.h"

#include <guard/check.h>
#include <painting2/OBB.h>
#include <painting2/SRT.h>
#include <node0/SceneNode.h>

namespace n2
{

const char* const CompBoundingBox::TYPE_NAME = "n2_bounding_box";

std::unique_ptr<n0::NodeUniqueComp> CompBoundingBox::Clone(const n0::SceneNode& node) const
{
	auto comp = std::make_unique<CompBoundingBox>();
	comp->m_size = m_size;
	comp->m_bounding = GetBounding(node).Clone2();
	return comp;
}

void CompBoundingBox::SetSize(const n0::SceneNode& node, const sm::rect& size)
{
	m_size = size;
	node.SetFlag<n2::NodeBoundingDirty>(true);
}

void CompBoundingBox::Build(const n0::SceneNode& node, const pt2::SRT& srt) const
{
	if (!m_bounding) {
		m_bounding = std::make_unique<pt2::OBB>();
	}
	m_bounding->Build(m_size, srt.position, srt.angle, srt.scale, srt.shear, srt.offset);
	node.SetFlag<n2::NodeBoundingDirty>(false);
}

const pt2::BoundingBox& CompBoundingBox::GetBounding(const n0::SceneNode& node) const
{
	if (!m_bounding || node.GetFlag<n2::NodeBoundingDirty>())
	{
		auto& ctrans = node.GetUniqueComp<n2::CompTransform>();
		Build(node, ctrans.GetTrans().GetSRT());
	}
	return *m_bounding;
}

}