#include "node2/CompBoundingBox.h"
#include "node2/NodeFlags.h"
#include "node2/CompTransform.h"

#include <guard/check.h>
#include <painting2/OBB.h>
#include <painting2/SRT.h>
#include <node0/SceneNode.h>
#include <node0/NodeFlagsHelper.h>

namespace n2
{

const char* const CompBoundingBox::TYPE_NAME = "n2_bounding_box";

std::unique_ptr<n0::NodeComp> CompBoundingBox::Clone(const n0::SceneNode& node) const
{
	auto comp = std::make_unique<CompBoundingBox>();
	comp->m_size = m_size;
	comp->m_bounding = GetBounding(node).Clone2();
	return comp;
}

void CompBoundingBox::SetSize(const n0::SceneNode& node, const sm::rect& size)
{
	m_size = size;
	n0::NodeFlagsHelper::SetFlag<NodeBoundingDirty>(node, true);
}

void CompBoundingBox::Build(const n0::SceneNode& node, const pt2::SRT& srt) const
{
	if (!m_bounding) {
		m_bounding = std::make_unique<pt2::OBB>();
	}
	m_bounding->Build(m_size, srt.position, srt.angle, srt.scale, srt.shear, srt.offset);
	n0::NodeFlagsHelper::SetFlag<NodeBoundingDirty>(node, false);
}

const pt2::BoundingBox& CompBoundingBox::GetBounding(const n0::SceneNode& node) const
{
	if (!m_bounding || n0::NodeFlagsHelper::GetFlag<NodeBoundingDirty>(node))
	{
		auto& ctrans = node.GetUniqueComp<CompTransform>();
		Build(node, ctrans.GetTrans().GetSRT());
	}
	return *m_bounding;
}

}