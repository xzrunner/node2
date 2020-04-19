#pragma once

#include "predef.h"
#include N2_MAT_HEADER
#include <painting2/RenderReturn.h>
#include <painting2/RenderColorCommon.h>
#include <cu/cu_macro.h>
#include <SM_Matrix.h>
#include <SM_Rect.h>
#include <node0/typedef.h>
#include <node0/CompAsset.h>

#include <functional>
#include <vector>

namespace ur2 { class Device; class Context; struct RenderState; }
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

	void SetCamScale(float s) { m_cam_scale = s; }
	float GetCamScale() const { return m_cam_scale; }

    void  SetScreenRegion(const sm::rect& r) { m_screen_region = r; }
    auto& GetScreenRegion() const { return m_screen_region; }

private:
	N2_MAT mt;

	CompUniquePatch* patch;
	size_t node_id;

	bool is_edit_mode;

	bool m_quad_base_left_top;

	pt2::RenderColorCommon m_color;

	float m_cam_scale = 1.0f;

    sm::rect m_screen_region;

	friend class RenderSystem;

}; // RenderParams

class RenderSystem
{
public:
	pt2::RenderReturn Draw(const ur2::Device& dev, ur2::Context& ctx, ur2::RenderState& rs,
        const n0::SceneNodePtr& node, const RenderParams& rp = RenderParams());

	pt2::RenderReturn Draw(
        const ur2::Device& dev, ur2::Context& ctx, ur2::RenderState& rs,
		const n0::CompAsset& casset,
		const sm::vec2& pos = sm::vec2(0, 0),
		float angle = 0,
		const sm::vec2& scale = sm::vec2(1, 1),
		const sm::vec2& shear = sm::vec2(0, 0),
		const RenderParams& rp = RenderParams()
	);
	pt2::RenderReturn Draw(const ur2::Device& dev, ur2::Context& ctx, ur2::RenderState& rs,
        const n0::CompAsset& casset, const sm::Matrix2D& mat);

	void DrawScissorRect(const ur2::Device& dev, ur2::Context& ctx, ur2::RenderState& rs,
        const sm::rect& rect, float line_width, const N2_MAT& mt);

	void AddDrawAssetFunc(n0::AssetID id, std::function<void(const n0::CompAsset&, const n2::RenderParams&)> func);
	void AddDrawCompFunc(std::function<void(const ur2::Device&, ur2::Context&, const n0::SceneNode&, const n2::RenderParams&)> func);

private:
	pt2::RenderReturn DrawAsset(const ur2::Device& dev, ur2::Context& ctx, ur2::RenderState& rs,
        const n0::CompAsset& casset, RenderParams& rp);

private:
	std::vector<std::function<void(const n0::CompAsset&, const n2::RenderParams&)>> m_draw_asset_funcs;
	std::vector<std::function<void(const ur2::Device&, ur2::Context&, const n0::SceneNode&, const n2::RenderParams&)>> m_draw_comp_funcs;

	CU_SINGLETON_DECLARATION(RenderSystem)

}; // RenderSystem

}