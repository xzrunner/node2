#pragma once

#include <node0/NodeComp.h>
#include <painting2/RenderColorMap.h>

namespace n2
{

class CompColorMap : public n0::NodeComp
{
public:
	virtual const char* Type() const override { return TYPE_NAME; }
	virtual n0::CompID TypeID() const override {
		return n0::GetCompTypeID<CompColorMap>();
	}
	virtual std::unique_ptr<n0::NodeComp> Clone(const n0::SceneNode& node) const override;

	const pt2::RenderColorMap& GetColor() const { return m_col; }
	pt2::RenderColorMap& GetColor() { return m_col; }

	void SetColor(const pt2::RenderColorMap& col) { m_col = col; }

	void Reset();

	static const char* const TYPE_NAME;

private:
	pt2::RenderColorMap m_col;

}; // CompColorMap

}