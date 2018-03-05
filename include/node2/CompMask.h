#pragma once

#include <node0/CompAsset.h>
#include <node0/typedef.h>

#include <functional>

namespace n2
{

class CompMask : public n0::CompAsset
{
public:
	virtual const char* Type() const override { return TYPE_NAME; }

	virtual n0::AssetID AssetTypeID() const override {
		return n0::GetAssetUniqueTypeID<CompMask>();
	}
	virtual void Traverse(std::function<bool(const n0::SceneNodePtr&)> func) const;

	void SetBaseNode(const n0::SceneNodePtr& base) { m_base = base; }
	void SetMaskNode(const n0::SceneNodePtr& mask) { m_mask = mask; }
	const n0::SceneNodePtr& GetBaseNode() const { return m_base; }
	const n0::SceneNodePtr& GetMaskNode() const { return m_mask; }

	static const char* const TYPE_NAME;

private:
	n0::SceneNodePtr m_base = nullptr, m_mask = nullptr;

}; // CompMask

}