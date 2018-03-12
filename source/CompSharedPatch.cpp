#include "node2/CompSharedPatch.h"
#include "node2/EditOp.h"

#include <node0/CompAsset.h>
#include <node0/SceneNode.h>

#include <algorithm>

namespace n2
{

const char* const CompSharedPatch::TYPE_NAME = "n2_shared_patch";

std::unique_ptr<n0::NodeUniqueComp> CompSharedPatch::Clone(const n0::SceneNode& node) const
{
	auto comp = std::make_unique<CompSharedPatch>();
	comp->m_edit_ops = m_edit_ops;
	return comp;
}

void CompSharedPatch::AddEditOp(size_t node_id, std::unique_ptr<EditOp>& op)
{
	auto itr = std::lower_bound(m_edit_ops.begin(), m_edit_ops.end(), node_id, EditOpListLessThan());
	if (itr == m_edit_ops.end()) {
		m_edit_ops.push_back(EditOpList(node_id, op));
	} else if (node_id < itr->GetNodeID()) {
		m_edit_ops.insert(itr, EditOpList(node_id, op));
	} else {
		itr->AddEditOp(op);
	}
}

void CompSharedPatch::SetAllEditOp(const std::vector<EditOpList>& ops)
{
	m_edit_ops = ops;
}

void CompSharedPatch::PatchToNode(const n0::SceneNodePtr& node)
{
	if (m_edit_ops.empty()) {
		return;
	}

	size_t node_id = 0;
	auto ptr = m_edit_ops.begin();

	if (node_id == ptr->GetNodeID()) {
		PatchToNode(*ptr, node);
		++ptr;
	}
	node_id += 1;

	auto& casset = node->GetSharedComp<n0::CompAsset>();
	casset.Traverse([&](const n0::SceneNodePtr& node)->bool 
	{
		auto& _casset = node->GetSharedComp<n0::CompAsset>();
		if (node_id == ptr->GetNodeID()) {
			PatchToNode(*ptr, node);
		}

		node_id += 1;
	});
}

void CompSharedPatch::PatchToNode(const EditOpList& op_list, const n0::SceneNodePtr& node)
{

}

}
