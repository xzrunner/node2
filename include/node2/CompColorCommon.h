#pragma once

#include <node0/NodeComponent.h>
#include <painting2/RenderColorCommon.h>

namespace n2
{

class CompColorCommon : public n0::NodeComponent
{
public:
	virtual const char* Type() const override { return TYPE_NAME; }

	const pt2::RenderColorCommon& GetColor() const { return m_col; }
	pt2::RenderColorCommon& GetColor() { return m_col; }
	
	void SetColor(const pt2::RenderColorCommon& col) { m_col = col; }

	void Reset();

	static const char* const TYPE_NAME;

private:
	pt2::RenderColorCommon m_col;
	
}; // CompColorCommon

}