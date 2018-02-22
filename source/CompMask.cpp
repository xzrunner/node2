#include "node2/CompMask.h"

namespace n2
{

const char* const CompMask::TYPE_NAME = "mask";

bool CompMask::StoreToJson(rapidjson::Value& val, rapidjson::MemoryPoolAllocator<>& alloc) const
{
	return false;
}

void CompMask::LoadFromJson(const rapidjson::Value& val)
{
}

}