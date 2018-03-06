#pragma once

#include <node0/CompAsset.h>
#include <painting2/Text.h>

namespace n2
{

class CompText : public n0::CompAsset
{
public:
	virtual const char* Type() const override { return TYPE_NAME; }

	virtual n0::AssetID AssetTypeID() const override {
		return n0::GetAssetUniqueTypeID<CompText>();
	}
	virtual void Traverse(std::function<bool(const n0::SceneNodePtr&)> func) const {}
	virtual sm::rect GetBounding() const;

	const pt2::Text& GetText() const { return m_text; }
	pt2::Text& GetText() { return m_text; }

	void SetText(const pt2::Text& text) { m_text = text; }

	static const char* const TYPE_NAME;

private:
	pt2::Text m_text;

}; // CompText

}