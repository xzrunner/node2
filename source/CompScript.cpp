#include "node2/CompScript.h"

namespace n2
{

const char* const CompScript::TYPE_NAME = "n2_script";

std::unique_ptr<n0::NodeUniqueComp> CompScript::Clone(const n0::SceneNode& node) const
{
	auto comp = std::make_unique<CompScript>();
	comp->m_filepath = m_filepath;
	return comp;
}

void CompScript::SetFilepath(const std::string& filepath)
{
	m_filepath = filepath;
}

}