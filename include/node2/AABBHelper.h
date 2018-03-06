#pragma once

#include <SM_Rect.h>
#include <node0/typedef.h>

namespace n2
{

class AABBHelper
{
public:
	static void Combine(sm::rect& aabb, const n0::SceneNodePtr& child);

}; // AABBHelper

}