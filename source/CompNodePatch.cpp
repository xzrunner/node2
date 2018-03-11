#include "node2/CompNodePatch.h"
#include "node2/EditOp.h"

#include <guard/check.h>

#include <algorithm>

namespace
{

struct EditOpListLessThan
{
    bool operator() (const n2::EditOpList& left, const n2::EditOpList& right)
    {
        return left.GetNodeID() < right.GetNodeID();
    }
    bool operator() (const n2::EditOpList& left, uint32_t right)
    {
        return left.GetNodeID() < right;
    }
    bool operator() (uint32_t left, const n2::EditOpList& right)
    {
        return left < right.GetNodeID();
    }
};

}

namespace n2
{

const char* const CompNodePatch::TYPE_NAME = "n2_node_patch";

CompNodePatch::CompNodePatch()
	: m_unique_ptr(-1)
{
}

std::unique_ptr<n0::NodeUniqueComp> CompNodePatch::Clone(const n0::SceneNode& node) const
{
	auto comp = std::make_unique<CompNodePatch>();
	comp->m_unique_op = m_unique_op;
	return comp;
}

void CompNodePatch::Clear()
{
	m_unique_ptr = -1;

	m_unique_op.clear();
}

void CompNodePatch::AddUniqueOp(size_t node_id, std::unique_ptr<EditOp>& op)
{
	auto itr = std::lower_bound(m_unique_op.begin(), m_unique_op.end(), node_id, EditOpListLessThan());
	if (itr == m_unique_op.end()) {
		m_unique_op.push_back(EditOpList(node_id, op));
	} else if (node_id < itr->GetNodeID()) {
		m_unique_op.insert(itr, EditOpList(node_id, op));
	} else {
		itr->AddEditOp(op);
	}
}

bool CompNodePatch::HasUniqueOp(size_t node_id) const
{
	return m_unique_ptr >= 0 && static_cast<size_t>(m_unique_ptr) < m_unique_op.size()
		&& m_unique_op[m_unique_ptr].GetNodeID() == node_id;
}

const EditOpList& CompNodePatch::GetUniqueOp(size_t node_id)
{
	GD_ASSERT(m_unique_ptr >= 0 && static_cast<size_t>(m_unique_ptr) < m_unique_op.size() && m_unique_op[m_unique_ptr].GetNodeID() == node_id, "not exists");
	return m_unique_op[m_unique_ptr];
}

void CompNodePatch::Rewind()
{
	m_unique_ptr = -1;
}

void CompNodePatch::Seek(size_t node_id)
{
	if (m_unique_op.empty()) {
		m_unique_ptr = -1;
		return;
	}

	if (m_unique_ptr == -1) {
		m_unique_ptr = 0;
	}
	GD_ASSERT(m_unique_ptr >= 0 && static_cast<size_t>(m_unique_ptr) < m_unique_op.size(), "not exists");
	while (m_unique_op[m_unique_ptr].GetNodeID() < node_id) 
	{
		++m_unique_ptr;
		if (m_unique_ptr == m_unique_op.size()) {
			break;
		}
	}
	if (static_cast<size_t>(m_unique_ptr) >= m_unique_op.size()) {
		m_unique_ptr = -1;
	}
}

}