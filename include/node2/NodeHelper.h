#pragma once

#include <SM_Rect.h>

namespace n0 { class SceneNode; }

namespace n2
{

class NodeHelper
{
public:
	static void SetBoundingSize(n0::SceneNode& node, const sm::rect& sz);

}; // NodeHelper

}