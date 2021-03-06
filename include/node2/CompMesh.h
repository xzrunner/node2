#pragma once

#include <node0/CompAsset.h>
#include <node0/typedef.h>

#include <painting2/Mesh.h>

namespace n2
{

class CompMesh : public n0::CompAsset
{
public:
	virtual const char* Type() const override { return TYPE_NAME; }

	virtual n0::AssetID AssetTypeID() const override {
		return n0::GetAssetUniqueTypeID<CompMesh>();
	}
	virtual void Traverse(std::function<bool(const n0::SceneNodePtr&)> func,
		bool inverse = false) const override {}

	const std::unique_ptr<pt2::Mesh<n0::SceneNodePtr>>& GetMesh() const { return m_mesh; }
	std::unique_ptr<pt2::Mesh<n0::SceneNodePtr>>& GetMesh() { return m_mesh; }
	void SetMesh(std::unique_ptr<pt2::Mesh<n0::SceneNodePtr>>& mesh) { m_mesh = std::move(mesh); }

	static const char* const TYPE_NAME;

private:
	std::unique_ptr<pt2::Mesh<n0::SceneNodePtr>> m_mesh = nullptr;

}; // CompMesh

}