#pragma once

#include <node0/NodeUniqueComp.h>
#include <SM_Rect.h>

namespace n2
{

class CompScissor : public n0::NodeUniqueComp
{
public:
	virtual const char* Type() const override { return TYPE_NAME; }
	virtual n0::UniqueCompID TypeID() const override {
		return n0::GetUniqueCompTypeID<CompScissor>();
	}
	virtual std::unique_ptr<n0::NodeUniqueComp> Clone(const n0::SceneNode& node) const override;

	void SetRect(const sm::rect& r) { m_rect = r; }
	const sm::rect& GetRect() const { return m_rect; }

	static const char* const TYPE_NAME;

private:
	sm::rect m_rect;

}; // CompScissor

}