#include "node2/CompSprite2.h"

namespace n2
{

const char* const CompSprite2::TYPE_NAME = "sprite2";

bool CompSprite2::StoreToJson(rapidjson::Value& val, rapidjson::MemoryPoolAllocator<>& alloc) const
{
	return false;
}

void CompSprite2::LoadFromJson(const rapidjson::Value& val)
{
}

}