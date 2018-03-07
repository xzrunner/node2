#pragma once

#include <SM_Vector.h>
#include <SM_Rect.h>
#include <node0/NodeUniqueComp.h>
#include <painting2/BoundingBox.h>

#include <memory>

namespace pt2 { class SRT; }
namespace n0 { class SceneNode; }

namespace n2
{

class CompBoundingBox : public n0::NodeUniqueComp
{
public:
	CompBoundingBox() {}
	CompBoundingBox(const sm::rect& size) : m_size(size) {}

	virtual const char* Type() const override { return TYPE_NAME; }
	virtual n0::UniqueCompID TypeID() const override {
		return n0::GetUniqueCompTypeID<CompBoundingBox>();
	}
	virtual std::unique_ptr<n0::NodeUniqueComp> Clone(const n0::SceneNode& node) const override;

	void SetSize(const n0::SceneNode& node, const sm::rect& size);
	const sm::rect& GetSize() const { return m_size; }
	
	void Build(const n0::SceneNode& node, const pt2::SRT& srt) const;

	const pt2::BoundingBox& GetBounding(const n0::SceneNode& node) const;

	static const char* const TYPE_NAME;

private:
	sm::rect m_size;

	mutable std::unique_ptr<pt2::BoundingBox> m_bounding = nullptr;

}; // CompBoundingBox

}