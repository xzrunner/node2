#pragma once

#include "node2/EditOp.h"

#include <memory>

namespace n2
{

class EditOpFunc
{
public:
	static size_t Size(const EditOp& op);

	static std::unique_ptr<EditOp> Clone(const EditOp& op);

	static void Copy(EditOp& dst, const EditOp& src);

}; // EditOpFunc

}