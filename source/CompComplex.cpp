#include "node2/CompComplex.h"
#include "node2/AABBHelper.h"

#include <node0/SceneNode.h>
#include <node2/CompTransform.h>

namespace n2
{

const char* const CompComplex::TYPE_NAME = "n2_complex";

//std::shared_ptr<NodeComponent> CompComplex::Clone() const
//{
//	auto comp = std::make_shared<CompComplex>();
//	comp->m_children.reserve(m_children.size());
//	for (auto& child : m_children) {
//		comp->m_children.push_back(child->Clone());
//	}
//	return comp;
//}

void CompComplex::Traverse(std::function<bool(const n0::SceneNodePtr&)> func, bool inverse) const
{
	if (inverse)
	{
		for (auto& itr = m_children.rbegin(); itr != m_children.rend(); ++itr) {
			if (!func(*itr)) {
				break;
			}
		}
	}
	else
	{
		for (auto& child : m_children) {
			if (!func(child)) {
				break;
			}
		}
	}
}

sm::rect CompComplex::GetBounding() const
{
	sm::rect aabb;
	for (auto& child : m_children) {
		AABBHelper::Combine(aabb, child);
	}
	return aabb;
}

void CompComplex::AddChild(const std::shared_ptr<n0::SceneNode>& child)
{
	m_children.push_back(child);

	auto& casset = child->GetSharedComp<n0::CompAsset>();
	m_node_count += casset.GetNodeCount();
}

bool CompComplex::RemoveChild(const std::shared_ptr<n0::SceneNode>& child)
{
	for (auto itr = m_children.begin(); itr != m_children.end(); ++itr) 
	{
		if (*itr == child) 
		{
			m_children.erase(itr);

			auto& casset = child->GetSharedComp<n0::CompAsset>();
			m_node_count -= casset.GetNodeCount();

			return true;
		}
	}
	return false;
}

void CompComplex::RemoveAllChildren()
{
	m_children.clear();
	m_node_count = 1;
}

void CompComplex::SetChildren(const std::vector<n0::SceneNodePtr>& children)
{
	m_children = children;

	for (auto& child : children) 
	{
		auto& casset = child->GetSharedComp<n0::CompAsset>();
		m_node_count += casset.GetNodeCount();
	}
}

}