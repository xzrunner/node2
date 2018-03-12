#include "node2/CompUniquePatch.h"
#include "node2/EditOp.h"

#include <guard/check.h>

#include <algorithm>

namespace n2
{

const char* const CompUniquePatch::TYPE_NAME = "n2_unique_patch";

CompUniquePatch::CompUniquePatch()
	: m_unique_ptr(-1)
{
}

std::unique_ptr<n0::NodeUniqueComp> CompUniquePatch::Clone(const n0::SceneNode& node) const
{
	auto comp = std::make_unique<CompUniquePatch>();
	comp->m_edit_ops = m_edit_ops;
	return comp;
}

void CompUniquePatch::Clear()
{
	m_unique_ptr = -1;

	m_edit_ops.clear();
}

void CompUniquePatch::AddEditOp(size_t node_id, std::unique_ptr<EditOp>& op)
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

void CompUniquePatch::SetAllEditOp(const std::vector<EditOpList>& ops)
{
	m_edit_ops = ops;
}

bool CompUniquePatch::HasEditOp(size_t node_id) const
{
	return m_unique_ptr >= 0 && static_cast<size_t>(m_unique_ptr) < m_edit_ops.size()
		&& m_edit_ops[m_unique_ptr].GetNodeID() == node_id;
}

const EditOpList& CompUniquePatch::GetEditOp(size_t node_id)
{
	GD_ASSERT(m_unique_ptr >= 0 && static_cast<size_t>(m_unique_ptr) < m_edit_ops.size() && m_edit_ops[m_unique_ptr].GetNodeID() == node_id, "not exists");
	return m_edit_ops[m_unique_ptr];
}

void CompUniquePatch::Rewind()
{
	m_unique_ptr = -1;
}

void CompUniquePatch::Seek(size_t node_id)
{
	if (m_edit_ops.empty()) {
		m_unique_ptr = -1;
		return;
	}

	if (m_unique_ptr == -1) {
		m_unique_ptr = 0;
	}
	GD_ASSERT(m_unique_ptr >= 0 && static_cast<size_t>(m_unique_ptr) < m_edit_ops.size(), "not exists");
	while (m_edit_ops[m_unique_ptr].GetNodeID() < node_id) 
	{
		++m_unique_ptr;
		if (m_unique_ptr == m_edit_ops.size()) {
			break;
		}
	}
	if (static_cast<size_t>(m_unique_ptr) >= m_edit_ops.size()) {
		m_unique_ptr = -1;
	}
}

}