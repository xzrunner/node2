#include "node2/CompScript.h"

namespace n2
{

const char* const CompScript::TYPE_NAME = "n2_script";

std::unique_ptr<n0::NodeUniqueComp> CompScript::Clone(const n0::SceneNode& node) const
{
	auto comp = std::make_unique<CompScript>();
	return comp;
}

void CompScript::SetFilepath(const std::string& filepath, const n0::SceneNodePtr& node)
{
	if (m_filepath == filepath) {
		return;
	}

	m_filepath = filepath;
	m_script.LoadScript(m_filepath, node);
}

void CompScript::Reload()
{
//	m_script.LoadScript(m_filepath);
}

}