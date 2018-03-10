#pragma once

#include "predef.h"
#include N2_MAT_HEADER
#include "painting2/RenderReturn.h"

#include <SM_Matrix.h>
#include <node0/typedef.h>

namespace n2
{

class CompNodePatch;

class RenderSystem
{
public:
	static pt2::RenderReturn Draw(const n0::SceneNodePtr& node, const N2_MAT& mt, 
		CompNodePatch* patch, size_t node_id);

}; // RenderSystem

}