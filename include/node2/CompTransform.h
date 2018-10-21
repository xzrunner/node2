#pragma once

#include <node0/NodeComp.h>
#include <painting2/GeoTransform.h>

namespace n0 { class SceneNode; }

namespace n2
{

class CompTransform : public n0::NodeComp
{
public:
	virtual const char* Type() const override { return TYPE_NAME; }
	virtual n0::CompID TypeID() const override {
		return n0::GetCompTypeID<CompTransform>();
	}
	virtual std::unique_ptr<n0::NodeComp> Clone(const n0::SceneNode& node) const override;

	const pt2::GeoTransform& GetTrans() const { return m_trans; }
//	pt2::GeoTransform& GetTrans() { return m_trans; }

	void SetPosition(const n0::SceneNode& node, const sm::vec2& pos);
	void SetAngle(const n0::SceneNode& node, float angle);
	void SetScale(const n0::SceneNode& node, const sm::vec2& scale);
	void SetShear(const n0::SceneNode& node, const sm::vec2& shear);
	void SetOffset(const n0::SceneNode& node, const sm::vec2& offset);

	void SetSRT(const n0::SceneNode& node, const pt2::SRT& srt);
	void SetSRT(const pt2::SRT& srt);

	static const char* const TYPE_NAME;

private:
	pt2::GeoTransform m_trans;

}; // CompTransform

}