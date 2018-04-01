#pragma once

#include <node0/CompAsset.h>
#include <node0/typedef.h>

namespace et { class P3dTemplate; }

namespace n2
{

class CompParticle3d : public n0::CompAsset
{
public:
	CompParticle3d(int max_sym_count);

	virtual const char* Type() const override { return TYPE_NAME; }

	virtual n0::AssetID AssetTypeID() const override {
		return n0::GetAssetUniqueTypeID<CompParticle3d>();
	}
	virtual void Traverse(std::function<bool(const n0::SceneNodePtr&)> func,
		bool inverse = false) const override;
	virtual sm::rect GetBounding() const override;

	const et::P3dTemplate& GetP3DTemp() const { return *m_p3d_temp; }
	et::P3dTemplate& GetP3DTemp() { return *m_p3d_temp; }

	static const char* const TYPE_NAME;

private:
	std::unique_ptr<et::P3dTemplate> m_p3d_temp = nullptr;

}; // CompParticle3d

}