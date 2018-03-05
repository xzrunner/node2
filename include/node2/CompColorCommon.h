#pragma once

#include <node0/NodeUniqueComp.h>
#include <painting2/RenderColorCommon.h>

namespace ee0 { class SubjectMgr; }

namespace n2
{

class CompColorCommon : public n0::NodeUniqueComp
{
public:
	virtual const char* Type() const override { return TYPE_NAME; }
	virtual n0::UniqueCompID TypeID() const override { 
		return n0::GetUniqueCompTypeID<CompColorCommon>(); 
	}
	virtual std::unique_ptr<n0::NodeUniqueComp> Clone() const override;

	const pt2::RenderColorCommon& GetColor() const { return m_col; }
	pt2::RenderColorCommon& GetColor() { return m_col; }
	
	void SetColor(const pt2::RenderColorCommon& col) { m_col = col; }

	void Reset();

	static const char* const TYPE_NAME;

private:
	pt2::RenderColorCommon m_col;
	
}; // CompColorCommon

}