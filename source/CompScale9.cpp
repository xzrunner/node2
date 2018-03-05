#include "node2/CompScale9.h"
#include "node2/CompBoundingBox.h"

#include <node0/SceneNode.h>
#include <node2/CompTransform.h>

#include <algorithm>

namespace n2
{

const char* const CompScale9::TYPE_NAME = "n2_scale9";

CompScale9::CompScale9()
	: m_type(S9_NULL)
	, m_width(200)
	, m_height(200)
{
	m_sz_left = m_sz_right = m_sz_top = m_sz_down = 0;
}

//std::unique_ptr<n0::NodeComponent> CompScale9::Clone() const
//{
//	auto comp = std::make_unique<CompScale9>();
//
//	comp->m_type = m_type;
//
//	comp->m_width  = m_width;
//	comp->m_height = m_height;
//
//	for (int i = 0; i < 9; ++i) {
//		if (m_grids[i]) {
//			comp->m_grids[i] = m_grids[i]->Clone();
//		}
//	}
//
//	comp->m_sz_left  = m_sz_left;
//	comp->m_sz_right = m_sz_right;
//	comp->m_sz_top   = m_sz_top;
//	comp->m_sz_down  = m_sz_down;
//
//	return comp;
//}

void CompScale9::Traverse(std::function<bool(const n0::SceneNodePtr&)> func) const
{
	for (int i = 0; i < 9; ++i) {
		if (m_grids[i]) {
			func(m_grids[i]);
		}
	}
}

void CompScale9::SetWidth(float width)
{
	if (m_width != width) {
		SetSize(width, m_height);
	}
}

void CompScale9::SetHeight(float height)
{
	if (m_height != height) {
		SetSize(m_width, height);
	}
}

void CompScale9::SetSize(float width, float height)
{
	if (m_width == width && m_height == height) {
		return;
	}

	m_width  = width;
	m_height = height;

	switch (m_type)
	{
	case S9_9GRID:
		{
			float w0 = GetLeftWidth(),
				  w2 = GetRightWidth(),
				  w1 = width - w0 - w2;
			float h0 = GetDownHeight(),
				  h2 = GetTopHeight(),
				  h1 = height - h0 - h2;

			ResizeNode(S9_DOWN_LEFT, sm::vec2(-w0*0.5f-w1*0.5f, -h0*0.5f-h1*0.5f), w0, h0, true, true);
			ResizeNode(S9_DOWN_CENTER, sm::vec2(0.0f, -h0*0.5f-h1*0.5f), w1, h0, false, true);
			ResizeNode(S9_DOWN_RIGHT, sm::vec2(w1*0.5f+w2*0.5f, -h0*0.5f-h1*0.5f), w2, h0, true, true);

			ResizeNode(S9_MID_LEFT, sm::vec2(-w0*0.5f-w1*0.5f, 0.0f), w0, h1, true, false);
			ResizeNode(S9_MID_CENTER, sm::vec2(0.0f, 0.0f), w1, h1, false, false);
			ResizeNode(S9_MID_RIGHT, sm::vec2(w1*0.5f+w2*0.5f, 0.0f), w2, h1, true, false);

			ResizeNode(S9_TOP_LEFT, sm::vec2(-w0*0.5f-w1*0.5f, h1*0.5f+h2*0.5f), w0, h2, true, true);
			ResizeNode(S9_TOP_CENTER, sm::vec2(0.0f, h1*0.5f+h2*0.5f), w1, h2, false, true);
			ResizeNode(S9_TOP_RIGHT, sm::vec2(w1*0.5f+w2*0.5f, h1*0.5f+h2*0.5f), w2, h2, true, true);
		}
		break;
	case S9_9GRID_HOLLOW:
		{
			float w0 = GetLeftWidth(),
				  w2 = GetRightWidth(),
				  w1 = width - w0 - w2;
			float h0 = GetDownHeight(),
				  h2 = GetTopHeight(),
				  h1 = height - h0 - h2;

			ResizeNode(S9_DOWN_LEFT, sm::vec2(-w0*0.5f-w1*0.5f, -h0*0.5f-h1*0.5f), w0, h0, true, true);
			ResizeNode(S9_DOWN_CENTER, sm::vec2(0.0f, -h0*0.5f-h1*0.5f), w1, h0, false, true);
			ResizeNode(S9_DOWN_RIGHT, sm::vec2(w1*0.5f+w2*0.5f, -h0*0.5f-h1*0.5f), w2, h0, true, true);

			ResizeNode(S9_MID_LEFT, sm::vec2(-w0*0.5f-w1*0.5f, 0.0f), w0, h1, true, false);
			ResizeNode(S9_MID_RIGHT, sm::vec2(w1*0.5f+w2*0.5f, 0.0f), w2, h1, true, false);

			ResizeNode(S9_TOP_LEFT, sm::vec2(-w0*0.5f-w1*0.5f, h1*0.5f+h2*0.5f), w0, h2, true, true);
			ResizeNode(S9_TOP_CENTER, sm::vec2(0.0f, h1*0.5f+h2*0.5f), w1, h2, false, true);
			ResizeNode(S9_TOP_RIGHT, sm::vec2(w1*0.5f+w2*0.5f, h1*0.5f+h2*0.5f), w2, h2, true, true);
		}
		break;
	case S9_6GRID_UPPER:
		{
			float w0 = GetLeftWidth(),
				  w2 = GetRightWidth(),
				  w1 = width - w0 - w2;
			float h2 = GetTopHeight(),
				  h1 = height - h2;

			ResizeNode(S9_MID_LEFT, sm::vec2(-w0*0.5f-w1*0.5f, 0.0f), w0, h1, true, false);
			ResizeNode(S9_MID_CENTER, sm::vec2(0.0f, 0.0f), w1, h1, false, false);
			ResizeNode(S9_MID_RIGHT, sm::vec2(w1*0.5f+w2*0.5f, 0.0f), w2, h1, true, false);

			ResizeNode(S9_TOP_LEFT, sm::vec2(-w0*0.5f-w1*0.5f, h1*0.5f+h2*0.5f), w0, h2, true, true);
			ResizeNode(S9_TOP_CENTER, sm::vec2(0.0f, h1*0.5f+h2*0.5f), w1, h2, false, true);
			ResizeNode(S9_TOP_RIGHT, sm::vec2(w1*0.5f+w2*0.5f, h1*0.5f+h2*0.5f), w2, h2, true, true);
		}
		break;
	case S9_3GRID_HORI:
		{
			float w0 = GetLeftWidth(),
				  w2 = GetRightWidth(),
				  w1 = width - w0 - w2; 

			ResizeNode(S9_MID_LEFT, sm::vec2(-w0*0.5f-w1*0.5f, 0.0f), w0, height, true, true);
			ResizeNode(S9_MID_CENTER, sm::vec2(0.0f, 0.0f), w1, height, false, true);
			ResizeNode(S9_MID_RIGHT, sm::vec2(w1*0.5f+w2*0.5f, 0.0f), w2, height, true, true);
		}
		break;
	case S9_3GRID_VERT:
		{
			float h0 = GetDownHeight(),
				  h2 = GetTopHeight(),
				  h1 = height - h0 - h2;

			ResizeNode(S9_DOWN_CENTER, sm::vec2(0.0f, -h0*0.5f-h1*0.5f), width, h0, true, true);
			ResizeNode(S9_MID_CENTER, sm::vec2(0.0f, 0.0f), width, h1, true, false);
			ResizeNode(S9_TOP_CENTER, sm::vec2(0.0f, h1*0.5f+h2*0.5f), width, h2, true, true);
		}
		break;
	default:
		break;
	}
}

void CompScale9::Build(Scale9Type type, float w, float h, n0::SceneNodePtr grids[9],
	                   int sz_left, int sz_right, int sz_top, int sz_down)
{
	m_type = type;
	m_width = m_height = 0;
	for (int i = 0; i < 9; ++i) 
	{
		auto& src = grids[i];
		if (src) {
			m_grids[i] = src->Clone();
		} else {
			m_grids[i] = nullptr;
		}
	}
	m_sz_left  = sz_left;
	m_sz_right = sz_right;
	m_sz_top   = sz_top;
	m_sz_down  = sz_down;
	SetSize(static_cast<float>(w), static_cast<float>(h));
}

CompScale9::Scale9Type CompScale9::CheckType(const n0::SceneNodePtr grids[9])
{
	Scale9Type type = S9_NULL;
	do {
		// S9_9GRID
		type = S9_9GRID;
		for (int i = 0; i < 9; ++i) {
			if (!grids[i]) {
				type = S9_NULL;
				break;
			}
		}
		if (type != S9_NULL) break;

		// S9_9GRID_HOLLOW
		type = S9_9GRID_HOLLOW;
		for (int i = 0; i < 9; ++i) {
			if (i == 4) {
				continue;
			}
			if (!grids[i]) {
				type = S9_NULL;
				break;
			}
		}
		if (type != S9_NULL) break;

		// S9_6GRID_UPPER
		type = S9_6GRID_UPPER;
		for (int i = 3; i < 9; ++i) {
			if (!grids[i]) {
				type = S9_NULL;
				break;
			}
		}
		if (type != S9_NULL) break;

		// S9_3GRID_HORI
		if (grids[3] && grids[4] && grids[5]) {
			type = S9_3GRID_HORI;			
		}

		// S9_3GRID_VERT
		if (grids[1] && grids[4] && grids[7]) {
			type = S9_3GRID_VERT;
		}
	} while (false);
	return type;
}

void CompScale9::ResizeNode(Scale9Idx idx, const sm::vec2& center, float dst_w, 
	                          float dst_h, bool no_scale_w, bool no_scale_h)
{
	if (idx < 0 || idx >= 9 || !m_grids[idx]) {
		return;
	}

	auto& node = m_grids[idx];

	if (dst_w < 0) { dst_w = 1; }
	if (dst_h < 0) { dst_h = 1; }

	auto& ctrans = node->GetUniqueComp<CompTransform>();
	auto& trans = ctrans.GetTrans();
	trans.SetPosition(center);

	float src_w, src_h;
	auto& cbb = node->GetUniqueComp<CompBoundingBox>();
	auto& cbb_sz = cbb.GetSize();
	src_w = cbb_sz.Width();
	src_h = cbb_sz.Height();
	if (src_w == 0 || src_h == 0) {
		return;
	}

	const float times = trans.GetAngle() / SM_PI;
	bool rotate = fabs(times - (int)times) > 0.1f;
	if (m_sz_left != 0 && m_sz_right != 0 && m_sz_top != 0 && m_sz_down != 0)
	{
		if (rotate)
		{
			switch (idx)
			{
			case S9_DOWN_LEFT:
				src_h = static_cast<float>(m_sz_left);
				src_w = static_cast<float>(m_sz_down);
				break;
			case S9_DOWN_CENTER:
				src_w = static_cast<float>(m_sz_down);
				break;
			case S9_DOWN_RIGHT:
				src_h = static_cast<float>(m_sz_right);
				src_w = static_cast<float>(m_sz_down);
				break;
			case S9_MID_LEFT:
				src_h = static_cast<float>(m_sz_left);
				break;
			case S9_MID_RIGHT:
				src_h = static_cast<float>(m_sz_right);
				break;
			case S9_TOP_LEFT:
				src_h = static_cast<float>(m_sz_left);
				src_w = static_cast<float>(m_sz_top);
				break;
			case S9_TOP_CENTER:
				src_w = static_cast<float>(m_sz_top);
				break;
			case S9_TOP_RIGHT:
				src_h = static_cast<float>(m_sz_right);
				src_w = static_cast<float>(m_sz_top);
				break;
			default:
				break;
			}
		}
		else
		{
			switch (idx)
			{
			case S9_DOWN_LEFT:
				src_w = static_cast<float>(m_sz_left);
				src_h = static_cast<float>(m_sz_down);
				break;
			case S9_DOWN_CENTER:
				src_h = static_cast<float>(m_sz_down);
				break;
			case S9_DOWN_RIGHT:
				src_w = static_cast<float>(m_sz_right);
				src_h = static_cast<float>(m_sz_down);
				break;
			case S9_MID_LEFT:
				src_w = static_cast<float>(m_sz_left);
				break;
			case S9_MID_RIGHT:
				src_w = static_cast<float>(m_sz_right);
				break;
			case S9_TOP_LEFT:
				src_w = static_cast<float>(m_sz_left);
				src_h = static_cast<float>(m_sz_top);
				break;
			case S9_TOP_CENTER:
				src_h = static_cast<float>(m_sz_top);
				break;
			case S9_TOP_RIGHT:
				src_w = static_cast<float>(m_sz_right);
				src_h = static_cast<float>(m_sz_top);
				break;
			default:
				break;
			}
		}
	}

	const sm::vec2& old_scale = trans.GetScale();
	sm::vec2 new_scale;	
	if (rotate) {
		new_scale.x = no_scale_h ? 1 : dst_h / src_w;
		new_scale.y = no_scale_w ? 1 : dst_w / src_h;
	} else {
		new_scale.x = no_scale_w ? 1 : dst_w / src_w;
		new_scale.y = no_scale_h ? 1 : dst_h / src_h;
	}
	if (old_scale.x < 0) {
		new_scale.x = -new_scale.x;
	}
	if (old_scale.y < 0) {
		new_scale.y = -new_scale.y;
	}
	trans.SetScale(new_scale);

	auto& pos = trans.GetPosition();
	auto& offset = trans.GetOffset();
	auto  angle = trans.GetAngle();
	trans.SetPosition(pos + sm::rotate_vector(offset, angle) - offset);
}

sm::vec2 CompScale9::GetChildSize(Scale9Idx idx) const
{
	if (idx < 0 || idx >= 9 || !m_grids[idx]) {
		return sm::vec2(0, 0);
	}

	auto& node = m_grids[idx];
	auto& cbb = node->GetUniqueComp<CompBoundingBox>();
	auto& sz = cbb.GetSize();
	return sm::vec2(sz.Width(), sz.Height());
}

float CompScale9::GetLeftWidth() const
{
	return m_sz_left == 0 ?
		std::max(std::max(GetChildSize(S9_DOWN_LEFT).x, GetChildSize(S9_MID_LEFT).x), GetChildSize(S9_TOP_LEFT).x) : m_sz_left;
}

float CompScale9::GetRightWidth() const
{
	return m_sz_right == 0 ?
		std::max(std::max(GetChildSize(S9_DOWN_RIGHT).x, GetChildSize(S9_MID_RIGHT).x), GetChildSize(S9_TOP_RIGHT).x) : m_sz_right;
}

float CompScale9::GetDownHeight() const
{
	return m_sz_down == 0 ?
		std::max(std::max(GetChildSize(S9_DOWN_LEFT).y, GetChildSize(S9_DOWN_CENTER).y), GetChildSize(S9_DOWN_RIGHT).y) : m_sz_down;
}

float CompScale9::GetTopHeight() const
{
	return m_sz_top == 0 ?
		std::max(std::max(GetChildSize(S9_TOP_LEFT).y, GetChildSize(S9_TOP_CENTER).y), GetChildSize(S9_TOP_RIGHT).y) : m_sz_top;
}

}