#include "node2/CompUniquePatch.h"
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

const char* const CompUniquePatch::TYPE_NAME = "n2_unique_patch";

CompUniquePatch::CompUniquePatch()
	: m_unique_ptr(-1)
{
}

std::unique_ptr<n0::NodeUniqueComp> CompUniquePatch::Clone(const n0::SceneNode& node) const
{
	auto comp = std::make_unique<CompUniquePatch>();
	comp->m_operators = m_operators;
	return comp;
}

void CompUniquePatch::Clear()
{
	m_unique_ptr = -1;

	m_operators.clear();
}

void CompUniquePatch::AddUniqueOp(size_t node_id, std::unique_ptr<EditOp>& op)
{
	auto itr = std::lower_bound(m_operators.begin(), m_operators.end(), node_id, EditOpListLessThan());
	if (itr == m_operators.end()) {
		m_operators.push_back(EditOpList(node_id, op));
	} else if (node_id < itr->GetNodeID()) {
		m_operators.insert(itr, EditOpList(node_id, op));
	} else {
		itr->AddEditOp(op);
	}
}

bool CompUniquePatch::HasUniqueOp(size_t node_id) const
{
	return m_unique_ptr >= 0 && static_cast<size_t>(m_unique_ptr) < m_operators.size()
		&& m_operators[m_unique_ptr].GetNodeID() == node_id;
}

const EditOpList& CompUniquePatch::GetUniqueOp(size_t node_id)
{
	GD_ASSERT(m_unique_ptr >= 0 && static_cast<size_t>(m_unique_ptr) < m_operators.size() && m_operators[m_unique_ptr].GetNodeID() == node_id, "not exists");
	return m_operators[m_unique_ptr];
}

void CompUniquePatch::Rewind()
{
	m_unique_ptr = -1;
}

void CompUniquePatch::Seek(size_t node_id)
{
	if (m_operators.empty()) {
		m_unique_ptr = -1;
		return;
	}

	if (m_unique_ptr == -1) {
		m_unique_ptr = 0;
	}
	GD_ASSERT(m_unique_ptr >= 0 && static_cast<size_t>(m_unique_ptr) < m_operators.size(), "not exists");
	while (m_operators[m_unique_ptr].GetNodeID() < node_id) 
	{
		++m_unique_ptr;
		if (m_unique_ptr == m_operators.size()) {
			break;
		}
	}
	if (static_cast<size_t>(m_unique_ptr) >= m_operators.size()) {
		m_unique_ptr = -1;
	}
}

}