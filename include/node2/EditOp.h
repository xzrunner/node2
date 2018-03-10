#pragma once

#include <SM_Matrix2D.h>

namespace n2
{

#define MAP_NODE_OPS_BASED_ON_TYPE(NODE_OP_FN) \
	NODE_OP_FN(SetTransformOp) \

#define NULLPTR_OP_FN(Type) nullptr,

#define BUILD_OP_LUT(OP_FN) \
        { MAP_NODE_OPS_BASED_ON_TYPE(OP_FN) }

#define IDENTITY_FN(Type) Type,
namespace EditOpID {
    enum {
		MAP_NODE_OPS_BASED_ON_TYPE(IDENTITY_FN)
        Count,
    };
}
static_assert(EditOpID::SetTransformOp == 0,
        "First index must be zero for LUTs to work");

#define SUPER(Type) EditOp(EditOpID::Type)

struct EditOp
{
	EditOp(unsigned int id) : id(id) {}

	const uint32_t id;

}; // DisplayOp

/************************************************************************/
/* transform                                                            */
/************************************************************************/

struct SetTransformOp : EditOp
{
	SetTransformOp(const sm::Matrix2D& mat)
		: SUPER(SetTransformOp)
		, mat(mat) {}

	sm::Matrix2D mat;

}; // SetTransformOp

}