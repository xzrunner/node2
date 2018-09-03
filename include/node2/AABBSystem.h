#pragma once

#include <SM_Rect.h>
#include <cu/cu_macro.h>
#include <node0/typedef.h>

#include <functional>
#include <vector>

namespace n0 { class CompAsset; }

namespace n2
{

class AABBSystem
{
public:
	static sm::rect GetBounding(const n0::CompAsset& casset);

	static void Combine(sm::rect& aabb, const n0::SceneNodePtr& child);

	sm::rect GetBounding(const n0::SceneNode& node);

	void AddGetBoundFunc(std::function<bool(const n0::SceneNode&, sm::rect& bound)> func);

private:
	std::vector<std::function<bool(const n0::SceneNode&, sm::rect& bound)>> m_get_bound_funcs;

	CU_SINGLETON_DECLARATION(AABBSystem)

}; // AABBSystem

}