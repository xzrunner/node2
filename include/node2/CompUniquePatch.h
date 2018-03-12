#pragma once

#include "node2/EditOpList.h"

#include <node0/NodeUniqueComp.h>

#include <vector>

namespace n2
{

class CompUniquePatch : public n0::NodeUniqueComp
{
public:
	CompUniquePatch();

	virtual const char* Type() const override { return TYPE_NAME; }
	virtual n0::UniqueCompID TypeID() const override {
		return n0::GetUniqueCompTypeID<CompUniquePatch>();
	}
	virtual std::unique_ptr<n0::NodeUniqueComp> Clone(const n0::SceneNode& node) const override;

	void Clear();

	void AddEditOp(size_t node_id, std::unique_ptr<EditOp>& op);

	const std::vector<EditOpList>& GetAllEditOp() const { return m_edit_ops; }
	void SetAllEditOp(const std::vector<EditOpList>& ops);

	bool HasEditOp(size_t node_id) const;
	const EditOpList& GetEditOp(size_t node_id);

	void Rewind();
	void Seek(size_t node_id);

	static const char* const TYPE_NAME;

private:
	std::vector<EditOpList> m_edit_ops;
	int m_unique_ptr;

}; // CompUniquePatch

}