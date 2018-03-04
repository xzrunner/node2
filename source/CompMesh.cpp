#include "node2/CompMesh.h"

namespace n2
{

const char* const CompMesh::TYPE_NAME = "n2_mesh";

std::unique_ptr<n0::NodeComponent> CompMesh::Clone() const
{
	auto comp = std::make_unique<CompMesh>();
	// todo
//	comp->m_mesh = m_mesh->Clone();
	return comp;
}

}