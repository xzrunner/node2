#pragma once

#include <SM_Vector.h>
#include <node0/CompAsset.h>
#include <node0/typedef.h>

#include <functional>

namespace n2
{

class CompScale9 : public n0::CompAsset
{
public:
	enum Scale9Type
	{
		S9_NULL = 0,
		S9_9GRID,
		S9_3GRID_HORI,
		S9_3GRID_VERT,
		S9_6GRID_UPPER,
		S9_9GRID_HOLLOW
	};

	enum Scale9Idx
	{
		S9_DOWN_LEFT   = 0,
		S9_DOWN_CENTER = 1,
		S9_DOWN_RIGHT  = 2,

		S9_MID_LEFT    = 3,
		S9_MID_CENTER  = 4,
		S9_MID_RIGHT   = 5,

		S9_TOP_LEFT    = 6,
		S9_TOP_CENTER  = 7,
		S9_TOP_RIGHT   = 8,
	};

public:
	CompScale9();

	virtual const char* Type() const override { return TYPE_NAME; }

	virtual n0::AssetID AssetTypeID() const override {
		return n0::GetAssetUniqueTypeID<CompScale9>();
	}
	virtual void Traverse(std::function<bool(const n0::SceneNodePtr&)> func) const override;
	virtual sm::rect GetBounding() const override;
	virtual void InitNodeCount() const { m_node_count = 1; }

	float GetWidth() const { return m_width; }
	float GetHeight() const { return m_height; }

	void SetWidth(float width);
	void SetHeight(float height);
	void SetSize(float width, float height);

	void Build(Scale9Type type, float w, float h, n0::SceneNodePtr grids[9],
		int sz_left, int sz_right, int sz_top, int sz_down);

	Scale9Type GetType() const { return m_type; }
	static Scale9Type CheckType(const n0::SceneNodePtr grids[9]);

	static const char* const TYPE_NAME;

private:
	void ResizeNode(Scale9Idx idx, const sm::vec2& center,
		float dst_w, float dst_h, bool no_scale_w, bool no_scale_h);

	sm::vec2 GetChildSize(Scale9Idx idx) const;

	float GetLeftWidth() const;
	float GetRightWidth() const;
	float GetDownHeight() const;
	float GetTopHeight() const;

private:
	Scale9Type m_type;

	float m_width, m_height;

	// 6 7 8
	// 3 4 5
	// 0 1 2
	n0::SceneNodePtr m_grids[9];

	int m_sz_left, m_sz_right, m_sz_top, m_sz_down;

}; // CompScale9

}