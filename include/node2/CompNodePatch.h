#pragma once

#include "node2/EditOpList.h"

#include <node0/NodeUniqueComp.h>

#include <vector>

namespace n2
{

struct EditOp;

class CompNodePatch : public n0::NodeUniqueComp
{
public:
	CompNodePatch();

	virtual const char* Type() const override { return TYPE_NAME; }
	virtual n0::UniqueCompID TypeID() const override {
		return n0::GetUniqueCompTypeID<CompNodePatch>();
	}
	virtual std::unique_ptr<n0::NodeUniqueComp> Clone(const n0::SceneNode& node) const override;

	void Clear();

	void AddUniqueOp(size_t node_id, std::unique_ptr<EditOp>& op);

	const std::vector<EditOpList>& GetAllUniqueOP() const { return m_unique_op; }
	void SetAllUniqueOP(const std::vector<EditOpList>& unique_op) {
		m_unique_op = unique_op;
	}

	bool HasUniqueOp(size_t node_id) const;
	const EditOpList& GetUniqueOp(size_t node_id);

	void Rewind();
	void Seek(size_t node_id);

	static const char* const TYPE_NAME;

private:
	std::vector<EditOpList> m_unique_op;
	int m_unique_ptr;

}; // CompNodePatch

}