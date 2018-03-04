#pragma once

#include <node0/NodeComponent.h>
#include <painting2/GeoTransform.h>

namespace n2
{

class CompTransform : public n0::NodeComponent
{
public:
	virtual const char* Type() const override { return TYPE_NAME; }
	virtual n0::ComponentID TypeID() const override { 
		return n0::GetComponentTypeID<CompTransform>(); }
	virtual std::unique_ptr<n0::NodeComponent> Clone() const override;

	const pt2::GeoTransform& GetTrans() const { return m_transform; }
	pt2::GeoTransform& GetTrans() { return m_transform; }

	static const char* const TYPE_NAME;

private:
	pt2::GeoTransform m_transform;

}; // CompTransform

}