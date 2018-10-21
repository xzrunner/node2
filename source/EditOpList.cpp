#include "node2/EditOpList.h"
#include "node2/EditOp.h"
#include "node2/EditOpMem.h"

#include <guard/check.h>

#include <algorithm>

namespace
{

struct EditOpLessThan
{
    bool operator() (const std::unique_ptr<n2::EditOp>& left, const std::unique_ptr<n2::EditOp>& right)
    {
        return left->id < right->id;
    }
    bool operator() (const std::unique_ptr<n2::EditOp>& left, uint32_t right)
    {
        return left->id < right;
    }
    bool operator() (uint32_t left, const std::unique_ptr<n2::EditOp>& right)
    {
        return left < right->id;
    }
};

}

namespace n2
{

EditOpList::EditOpList(size_t node_id)
	: m_node_id(node_id)
{
}

EditOpList::EditOpList(size_t node_id, std::unique_ptr<EditOp>& op)
	: m_node_id(node_id)
{
	m_op_bitset[op->id] = true;
	m_list.push_back(std::move(op));
}

EditOpList::EditOpList(const EditOpList& list)
	: m_node_id(list.m_node_id)
	, m_op_bitset(list.m_op_bitset)
{
	m_list.reserve(list.m_list.size());
	for (auto& op : list.m_list) {
		m_list.push_back(EditOpMem::Clone(*op));
	}
}

EditOpList& EditOpList::operator = (const EditOpList& list)
{
	if (this == &list) {
		return *this;
	}

	m_node_id = list.m_node_id;

	m_list.clear();
	m_list.reserve(list.m_list.size());
	for (auto& op : list.m_list) {
		m_list.push_back(EditOpMem::Clone(*op));
	}

	m_op_bitset = list.m_op_bitset;

	return *this;
}

bool EditOpList::HasEditOp(uint32_t id) const
{
	return m_op_bitset[id];
}

void EditOpList::AddEditOp(std::unique_ptr<EditOp>& op)
{
	if (HasEditOp(op->id))
	{
		auto& old_op = GetEditOp(op->id);
		EditOpMem::Copy(old_op, *op);
		memcpy(&old_op, op.get(), EditOpMem::Size(*op));
	}
	else
	{
		m_op_bitset[op->id] = true;
		m_list.insert(
			std::upper_bound(m_list.begin(), m_list.end(), op, EditOpLessThan()),
			std::move(op)
		);
	}
}

const EditOp& EditOpList::GetEditOp(uint32_t id) const
{
	GD_ASSERT(HasEditOp(id), "not find op");
	auto itr = std::lower_bound(m_list.begin(), m_list.end(), id, EditOpLessThan());
	return **itr;
}

EditOp& EditOpList::GetEditOp(uint32_t id)
{
	GD_ASSERT(HasEditOp(id), "not find op");
	auto itr = std::lower_bound(m_list.begin(), m_list.end(), id, EditOpLessThan());
	return **itr;
}

}