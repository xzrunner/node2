#pragma once

#include <node0/NodeComp.h>
#include <node0/typedef.h>

namespace gs { class Shape; }

namespace n2
{

class CompShape : public n0::NodeComp
{
public:
	CompShape(const std::shared_ptr<gs::Shape>& shape);

	virtual const char* Type() const override { return TYPE_NAME; }
	virtual n0::CompID TypeID() const override {
		return n0::GetCompTypeID<CompShape>();
	}
	virtual std::unique_ptr<n0::NodeComp> Clone(const n0::SceneNode& node) const override;

	void SetShape(const std::shared_ptr<gs::Shape>& shape) { m_shape = shape; }
	auto& GetShape() const { return m_shape; }

	static const char* const TYPE_NAME;

private:
	std::shared_ptr<gs::Shape> m_shape = nullptr;

}; // CompShape

}