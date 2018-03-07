#include "node2/CompTransform.h"
#include "node2/NodeFlags.h"

#include <node0/SceneNode.h>

namespace n2
{

const char* const CompTransform::TYPE_NAME = "n2_transform";

std::unique_ptr<n0::NodeUniqueComp> CompTransform::Clone(const n0::SceneNode& node) const
{
	auto comp = std::make_unique<CompTransform>();
	comp->m_trans = m_trans;
	return comp;
}

void CompTransform::SetPosition(const n0::SceneNode& node, const sm::vec2& pos)
{
	if (m_trans.SetPosition(pos)) {
		node.SetFlag<n2::NodeBoundingDirty>(true);
	}
}

void CompTransform::SetAngle(const n0::SceneNode& node, float angle)
{
	if (m_trans.SetAngle(angle)) {
		node.SetFlag<n2::NodeBoundingDirty>(true);
	}
}

void CompTransform::SetScale(const n0::SceneNode& node, const sm::vec2& scale)
{
	if (m_trans.SetScale(scale)) {
		node.SetFlag<n2::NodeBoundingDirty>(true);
	}
}

void CompTransform::SetShear(const n0::SceneNode& node, const sm::vec2& shear)
{
	if (m_trans.SetShear(shear)) {
		node.SetFlag<n2::NodeBoundingDirty>(true);
	}
}

void CompTransform::SetOffset(const n0::SceneNode& node, const sm::vec2& offset)
{
	if (m_trans.SetOffset(offset)) {
		node.SetFlag<n2::NodeBoundingDirty>(true);
	}
}

void CompTransform::SetSRT(const n0::SceneNode& node, const pt2::SRT& srt)
{
	if (m_trans.SetSRT(srt)) {
		node.SetFlag<n2::NodeBoundingDirty>(true);
	}
}

}