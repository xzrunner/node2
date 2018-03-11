#pragma once

#include <vector>
#include <memory>
#include <bitset>

namespace n2
{

struct EditOp;

class EditOpList
{
public:
	EditOpList(size_t node_id);
	EditOpList(size_t node_id, std::unique_ptr<EditOp>& op);
	EditOpList(const EditOpList& list);
	EditOpList& operator = (const EditOpList& list);

	size_t GetNodeID() const { return m_node_id; }

	bool HasEditOp(uint32_t id) const;

	void AddEditOp(std::unique_ptr<EditOp>& op);

	const EditOp& GetEditOp(uint32_t id) const;

	const std::vector<std::unique_ptr<EditOp>>& 
		GetAllEditOp() const { return m_list; }

private:
	EditOp& GetEditOp(uint32_t id);

private:
	size_t m_node_id;

	std::vector<std::unique_ptr<EditOp>> m_list;

	static const size_t MAX_OP_NUM = 32;
	std::bitset<MAX_OP_NUM> m_op_bitset;

}; // EditOpList

}