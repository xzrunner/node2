#pragma once

#include "predef.h"
#include N2_MAT_HEADER
#include "painting2/RenderReturn.h"

#include <SM_Matrix.h>
#include <node0/typedef.h>

namespace n2
{

class CompUniquePatch;

class RenderParams
{
public:
	RenderParams()
		: patch(nullptr), node_id(0), is_edit_mode(true) {}

	void SetPatch(CompUniquePatch* patch) { this->patch = patch; }

	void SetEditMode(bool edit) { is_edit_mode = edit; }

private:
	N2_MAT mt;

	CompUniquePatch* patch;
	size_t node_id;

	bool is_edit_mode;

	friend class RenderSystem;

}; // RenderParams

class RenderSystem
{
public:
	static pt2::RenderReturn Draw(const n0::SceneNodePtr& node, 
		const RenderParams& rp = RenderParams());

}; // RenderSystem

}