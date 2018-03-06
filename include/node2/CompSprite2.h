#pragma once

#include <node0/CompAsset.h>
#include <sprite2/Symbol.h>

#include <memory>

namespace n2
{

class CompSprite2 : public n0::CompAsset
{
public:
	virtual const char* Type() const override { return TYPE_NAME; }

	virtual n0::AssetID AssetTypeID() const override {
		return n0::GetAssetUniqueTypeID<CompSprite2>();
	}
	virtual void Traverse(std::function<bool(const n0::SceneNodePtr&)> func) const {}
	virtual sm::rect GetBounding() const;

	void SetFilepath(const std::string& filepath) { m_filepath = filepath; }
	const std::string& GetFilepath() const { return m_filepath; }

	void SetSymbol(const s2::SymPtr& sym) { m_sym = sym; }
	const s2::SymPtr& GetSymbol() const { return m_sym; }

	static const char* const TYPE_NAME;

private:
	std::string m_filepath;

	s2::SymPtr m_sym = nullptr;

}; // CompSprite2

}