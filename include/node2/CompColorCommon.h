#pragma once

#include <node0/NodeComp.h>
#include <painting2/RenderColorCommon.h>

namespace n2
{

class CompColorCommon : public n0::NodeComp
{
public:
	virtual const char* Type() const override { return TYPE_NAME; }
	virtual n0::CompID TypeID() const override {
		return n0::GetCompTypeID<CompColorCommon>();
	}
	virtual std::unique_ptr<n0::NodeComp> Clone(const n0::SceneNode& node) const override;

	const pt2::RenderColorCommon& GetColor() const { return m_col; }
	pt2::RenderColorCommon& GetColor() { return m_col; }

	void SetColor(const pt2::RenderColorCommon& col) { m_col = col; }

	void Reset();

	static const char* const TYPE_NAME;

private:
	pt2::RenderColorCommon m_col;

}; // CompColorCommon

}