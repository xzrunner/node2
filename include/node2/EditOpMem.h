#pragma once

#include <memory>

namespace n2
{

struct EditOp;

class EditOpMem
{
public:
	static size_t Size(const EditOp& op);

	static std::unique_ptr<EditOp> Clone(const EditOp& op);

	static void Copy(EditOp& dst, const EditOp& src);

}; // EditOpMem

}