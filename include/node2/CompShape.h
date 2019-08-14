#pragma once

#include <node0/CompAsset.h>
#include <node0/typedef.h>

namespace gs { class Shape2D; }

namespace n2
{

class CompShape : public n0::CompAsset
{
public:
	CompShape(const std::shared_ptr<gs::Shape2D>& shape);

    virtual const char* Type() const override { return TYPE_NAME; }

    virtual n0::AssetID AssetTypeID() const override {
        return n0::GetAssetUniqueTypeID<CompShape>();
    }
    virtual void Traverse(std::function<bool(const n0::SceneNodePtr&)> func,
        bool inverse = false) const override {}

	void SetShape(const std::shared_ptr<gs::Shape2D>& shape) { m_shape = shape; }
	auto& GetShape() const { return m_shape; }

	static const char* const TYPE_NAME;

private:
	std::shared_ptr<gs::Shape2D> m_shape = nullptr;

}; // CompShape

}