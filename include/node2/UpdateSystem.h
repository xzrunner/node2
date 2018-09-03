#pragma once

#include <cu/cu_macro.h>
#include <node0/typedef.h>

#include <functional>
#include <vector>

namespace n2
{

class UpdateSystem
{
public:
	bool Update(const n0::SceneNodePtr& node);

	void AddUpdateCompFunc(std::function<bool(const n0::SceneNode&)> func);

private:
	std::vector<std::function<bool(const n0::SceneNode&)>> m_update_comp_funcs;

	CU_SINGLETON_DECLARATION(UpdateSystem)

}; // UpdateSystem

}