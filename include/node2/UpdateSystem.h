#pragma once

#include <cu/cu_macro.h>
#include <node0/typedef.h>

#include <functional>
#include <vector>

namespace ur { class Device; }

namespace n2
{

class UpdateSystem
{
public:
	bool Update(const n0::SceneNodePtr& node, const ur::Device* dev = nullptr);

	void AddUpdateCompFunc(std::function<bool(const n0::SceneNode&, const ur::Device*)> func);

private:
	std::vector<std::function<bool(const n0::SceneNode&, const ur::Device*)>> m_update_comp_funcs;

	CU_SINGLETON_DECLARATION(UpdateSystem)

}; // UpdateSystem

}