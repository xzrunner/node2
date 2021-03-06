#pragma once

#include <SM_Vector.h>
#include <SM_Matrix2D.h>

namespace n2
{

#define MAP_NODE_OPS_BASED_ON_TYPE(NODE_OP_FN) \
	NODE_OP_FN(SetTransformMatOp) \
	NODE_OP_FN(SetPositionOp) \
	NODE_OP_FN(SetAngleOp) \
	NODE_OP_FN(SetScaleOp) \
	NODE_OP_FN(SetShearOp) \

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
static_assert(EditOpID::SetTransformMatOp == 0,
        "First index must be zero for LUTs to work");

#define SUPER(Type) EditOp(EditOpID::Type)

class EditOp
{
public:
	EditOp(unsigned int id) : id(id) {}

	const uint32_t id;

}; // EditOp

/************************************************************************/
/* transform                                                            */
/************************************************************************/

class SetTransformMatOp : public EditOp
{
public:
	SetTransformMatOp(const sm::Matrix2D& mat)
		: SUPER(SetTransformMatOp)
		, mat(mat) {}

	sm::Matrix2D mat;

	static const char* const TYPE_NAME;

}; // SetTransformMatOp

class SetPositionOp : public EditOp
{
public:
	SetPositionOp(const sm::vec2& pos)
		: SUPER(SetPositionOp)
		, pos(pos) {}

	sm::vec2 pos;

	static const char* const TYPE_NAME;

}; // SetPositionOp

class SetAngleOp : public EditOp
{
public:
	SetAngleOp(float angle)
		: SUPER(SetAngleOp)
		, angle(angle) {}

	float angle;

	static const char* const TYPE_NAME;

}; // SetAngleOp

class SetScaleOp : public EditOp
{
public:
	SetScaleOp(const sm::vec2& scale)
		: SUPER(SetScaleOp)
		, scale(scale) {}

	sm::vec2 scale;

	static const char* const TYPE_NAME;

}; // SetScaleOp

class SetShearOp : public EditOp
{
public:
	SetShearOp(const sm::vec2& shear)
		: SUPER(SetShearOp)
		, shear(shear) {}

	sm::vec2 shear;

	static const char* const TYPE_NAME;

}; // SetShearOp

}