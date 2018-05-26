#include "node2/CompTransform.h"
#include "node2/NodeFlags.h"

#include <node0/SceneNode.h>
#include <node0/NodeFlagsHelper.h>

namespace n2
{

const char* const CompTransform::TYPE_NAME = "n2_transform";

std::unique_ptr<n0::NodeComp> CompTransform::Clone(const n0::SceneNode& node) const
{
	auto comp = std::make_unique<CompTransform>();
	comp->m_trans = m_trans;
	return comp;
}

void CompTransform::SetPosition(const n0::SceneNode& node, const sm::vec2& pos)
{
	if (m_trans.SetPosition(pos)) {
		n0::NodeFlagsHelper::SetFlag<NodeBoundingDirty>(node, true);
	}
}

void CompTransform::SetAngle(const n0::SceneNode& node, float angle)
{
	if (m_trans.SetAngle(angle)) {
		n0::NodeFlagsHelper::SetFlag<NodeBoundingDirty>(node, true);
	}
}

void CompTransform::SetScale(const n0::SceneNode& node, const sm::vec2& scale)
{
	if (m_trans.SetScale(scale)) {
		n0::NodeFlagsHelper::SetFlag<NodeBoundingDirty>(node, true);
	}
}

void CompTransform::SetShear(const n0::SceneNode& node, const sm::vec2& shear)
{
	if (m_trans.SetShear(shear)) {
		n0::NodeFlagsHelper::SetFlag<NodeBoundingDirty>(node, true);
	}
}

void CompTransform::SetOffset(const n0::SceneNode& node, const sm::vec2& offset)
{
	if (m_trans.SetOffset(offset)) {
		n0::NodeFlagsHelper::SetFlag<NodeBoundingDirty>(node, true);
	}
}

void CompTransform::SetSRT(const n0::SceneNode& node, const pt2::SRT& srt)
{
	if (m_trans.SetSRT(srt)) {
		n0::NodeFlagsHelper::SetFlag<NodeBoundingDirty>(node, true);
	}
}

void CompTransform::SetSRT(const pt2::SRT& srt)
{
	m_trans.SetSRT(srt);
}

}