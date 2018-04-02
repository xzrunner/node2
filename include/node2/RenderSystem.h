#pragma once

#include "predef.h"
#include N2_MAT_HEADER
#include "painting2/RenderReturn.h"
#include "painting2/RenderColorCommon.h"

#include <SM_Matrix.h>
#include <SM_Rect.h>
#include <node0/typedef.h>

namespace n0 { class CompAsset; }

namespace n2
{

class CompUniquePatch;

class RenderParams
{
public:
	RenderParams()
		: patch(nullptr), node_id(0), is_edit_mode(true), m_quad_base_left_top(false) {}

	void SetPatch(CompUniquePatch* patch) { this->patch = patch; }

	void SetEditMode(bool edit) { is_edit_mode = edit; }

	const N2_MAT& GetMatrix() const { return mt; }
	void SetMatrix(const N2_MAT& mt) { this->mt = mt; }

	void QuadBaseLeftTop(bool left_top) { m_quad_base_left_top = left_top; }

	const pt2::RenderColorCommon& GetColor() const { return m_color; }
	void SetColor(const pt2::RenderColorCommon& color) { m_color = color; }

private:
	N2_MAT mt;

	CompUniquePatch* patch;
	size_t node_id;

	bool is_edit_mode;

	bool m_quad_base_left_top;

	pt2::RenderColorCommon m_color;

	friend class RenderSystem;

}; // RenderParams

class RenderSystem
{
public:
	static pt2::RenderReturn Draw(const n0::SceneNodePtr& node, 
		const RenderParams& rp = RenderParams());

	static pt2::RenderReturn Draw(
		const n0::CompAsset& casset, 
		const sm::vec2& pos = sm::vec2(0, 0),
		float angle = 0,
		const sm::vec2& scale = sm::vec2(1, 1),
		const sm::vec2& shear = sm::vec2(0, 0),
		const RenderParams& rp = RenderParams()
	);

	static void DrawScissorRect(const sm::rect& rect, const N2_MAT& mt);

private:
	static pt2::RenderReturn DrawAsset(const n0::CompAsset& casset, RenderParams& rp);

}; // RenderSystem

}