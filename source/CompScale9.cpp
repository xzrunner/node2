#include "node2/CompScale9.h"

namespace n2
{

const char* const CompScale9::TYPE_NAME = "n2_scale9";

CompScale9::CompScale9()
	: m_type(S9_NULL)
	, m_width(200)
	, m_height(200)
{
}

void CompScale9::Traverse(std::function<bool(const n0::SceneNodePtr&)> func) const
{
	for (int i = 0; i < 9; ++i) {
		if (m_grids[i]) {
			func(m_grids[i]);
		}
	}
}

void CompScale9::SetNode(int idx, const n0::SceneNodePtr& node)
{
	if (idx >= 0 && idx < 9) {
		m_grids[idx] = node;
	}
}

}