#include "node2/EditOpFunc.h"

#include <guard/check.h>

namespace n2
{

#define OP_SIZE(Type) \
		case EditOpID::Type: return sizeof(Type);
size_t EditOpFunc::Size(const EditOp& op)
{
	switch (op.id)
	{
		MAP_NODE_OPS_BASED_ON_TYPE(OP_SIZE)
	}
	return 0;
}

std::unique_ptr<EditOp> EditOpFunc::Clone(const EditOp& op)
{
	auto sz = Size(op);
	auto new_op = (EditOp*)malloc(sz);
	memcpy(new_op, &op, sz);
	return std::unique_ptr<EditOp>(new_op);
}

void EditOpFunc::Copy(EditOp& dst, const EditOp& src)
{
	GD_ASSERT(dst.id == src.id, "not same type");
	memcpy(&dst, &src, Size(src));
}

}