#pragma once

#include <SM_Rect.h>
#include <node0/typedef.h>

namespace n0 { class CompAsset; }

namespace n2
{

class AABBSystem
{
public:
	static sm::rect GetBounding(const n0::CompAsset& casset);

	static void Combine(sm::rect& aabb, const n0::SceneNodePtr& child);

}; // AABBSystem

}