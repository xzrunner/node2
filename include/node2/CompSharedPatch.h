#pragma once

#include "node2/EditOpList.h"

#include <node0/NodeUniqueComp.h>
#include <node0/typedef.h>

#include <vector>

namespace n2
{

class CompSharedPatch : public n0::NodeUniqueComp
{
public:
	virtual const char* Type() const override { return TYPE_NAME; }
	virtual n0::UniqueCompID TypeID() const override {
		return n0::GetUniqueCompTypeID<CompSharedPatch>();
	}
	virtual std::unique_ptr<n0::NodeUniqueComp> Clone(const n0::SceneNode& node) const override;

	void AddEditOp(size_t node_id, std::unique_ptr<EditOp>& op);

	const std::vector<EditOpList>& GetAllEditOp() const { return m_edit_ops; }
	void SetAllEditOp(const std::vector<EditOpList>& ops) {
		m_edit_ops = ops;
	}

	void PatchToNode(const n0::SceneNodePtr& node);

	static const char* const TYPE_NAME;

private:
	static void PatchToNode(const EditOpList& op_list, const n0::SceneNodePtr& node);

private:
	std::vector<EditOpList> m_edit_ops;

}; // CompSharedPatch

}