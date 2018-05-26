#include "node2/CompScript.h"

#include <guard/check.h>

namespace n2
{

const char* const CompScript::TYPE_NAME = "n2_script";

std::unique_ptr<n0::NodeComp> CompScript::Clone(const n0::SceneNode& node) const
{
	auto comp = std::make_unique<CompScript>();
	return comp;
}

void CompScript::Reload(const n0::SceneNodePtr& node)
{
	m_script.LoadScript(m_filepath, node);
}

}