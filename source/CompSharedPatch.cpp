#include "node2/CompSharedPatch.h"
#include "node2/EditOp.h"
#include "node2/CompTransform.h"

#include <guard/check.h>
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

	size_t curr_id = 0;
	auto curr_node = node;
	auto ptr_op = m_edit_ops.begin();
	while (ptr_op != m_edit_ops.end())
	{
		auto& casset = curr_node->GetSharedComp<n0::CompAsset>();
		curr_id += 1;
		casset.Traverse([&](const n0::SceneNodePtr& node)->bool
		{
			auto& _casset = node->GetSharedComp<n0::CompAsset>();
			if (ptr_op->GetNodeID() == curr_id)
			{
				PatchToNode(*ptr_op, node);
				++ptr_op;
				curr_node = node;
				return false;
			}
			else if (ptr_op->GetNodeID() < curr_id + _casset.GetNodeCount())
			{
				curr_node = node;
				return false;
			}
			else
			{
				curr_id += _casset.GetNodeCount();
				return true;
			}
		});
	}
}

void CompSharedPatch::PatchToNode(const EditOpList& op_list, const n0::SceneNodePtr& node)
{
	auto& ops = op_list.GetAllEditOp();
	for (auto& op : ops)
	{
		switch (op->id)
		{
		case EditOpID::SetPositionOp:
			{
				auto& ctrans = node->GetUniqueComp<CompTransform>();
				ctrans.SetPosition(*node, static_cast<SetPositionOp&>(*op.get()).pos);
			}
			break;
		case EditOpID::SetAngleOp:
			{
				auto& ctrans = node->GetUniqueComp<CompTransform>();
				ctrans.SetAngle(*node, static_cast<SetAngleOp&>(*op.get()).angle);
			}
			break;
		case EditOpID::SetScaleOp:
			{
				auto& ctrans = node->GetUniqueComp<CompTransform>();
				ctrans.SetScale(*node, static_cast<SetScaleOp&>(*op.get()).scale);
			}
			break;
		case EditOpID::SetShearOp:
			{
				auto& ctrans = node->GetUniqueComp<CompTransform>();
				ctrans.SetShear(*node, static_cast<SetShearOp&>(*op.get()).shear);
			}
			break;
		default:
			GD_REPORT_ASSERT("unknowno edit op type.");
		}
	}
}

}
