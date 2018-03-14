#pragma once

#include <node0/typedef.h>

namespace n2
{

class SceneTreeHelper
{
public:
	static void UpdateAABB(const n0::SceneNodePtr& node, 
		const n0::SceneNodePtr& root, size_t node_id);

}; // SceneTreeHelper

}