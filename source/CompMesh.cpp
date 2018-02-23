#include "node2/CompMesh.h"

namespace n2
{

const char* const CompMesh::TYPE_NAME = "mesh";

bool CompMesh::StoreToJson(rapidjson::Value& val, rapidjson::MemoryPoolAllocator<>& alloc) const
{
	return false;
}

void CompMesh::LoadFromJson(const rapidjson::Value& val)
{
}

}