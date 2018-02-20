#include "node2/CompText.h"

namespace n2
{

const char* const CompText::TYPE_NAME = "text";

bool CompText::StoreToJson(rapidjson::Value& val, rapidjson::MemoryPoolAllocator<>& alloc) const
{
	return false;
}

void CompText::LoadFromJson(const rapidjson::Value& val)
{
}

}