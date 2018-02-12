#pragma once

#include <node0/NodeComponent.h>
#include <painting2/RenderColorMap.h>

namespace n2
{

class CompColorMap : public n0::NodeComponent
{
public:
	virtual const char* Type() const override { return TYPE_NAME; }

	const pt2::RenderColorMap& GetColor() const { return m_col; }
	pt2::RenderColorMap& GetColor() { return m_col; }

	void SetColor(const pt2::RenderColorMap& col) { m_col = col; }

	void Reset();

	static const char* const TYPE_NAME;

private:
	pt2::RenderColorMap m_col;
	
}; // CompColorMap

}