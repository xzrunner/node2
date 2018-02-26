#pragma once

#include <node0/NodeComponent.h>
#include <node0/typedef.h>

#include <functional>

namespace n2
{

class CompScale9 : public n0::NodeComponent
{
public:
	CompScale9();

	virtual const char* Type() const override { return TYPE_NAME; }

	void Traverse(std::function<bool(const n0::SceneNodePtr&)> func) const;

	void SetNode(int idx, const n0::SceneNodePtr& node);

	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }
	void SetWidth(int width) { m_width = width; }
	void SetHeight(int height) { m_height = height; }

	static const char* const TYPE_NAME;

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
		S9_DOWN_LEFT	= 0,
		S9_DOWN_CENTER	= 1,
		S9_DOWN_RIGHT	= 2,

		S9_MID_LEFT		= 3,
		S9_MID_CENTER	= 4,
		S9_MID_RIGHT	= 5,

		S9_TOP_LEFT		= 6,
		S9_TOP_CENTER	= 7,
		S9_TOP_RIGHT	= 8,
	};

private:
	Scale9Type m_type;

	// 6 7 8
	// 3 4 5
	// 0 1 2
	n0::SceneNodePtr m_grids[9];

	int m_width, m_height;

}; // CompScale9

}