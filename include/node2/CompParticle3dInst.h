#pragma once

#include <node0/NodeUniqueComp.h>

namespace et { class P3dInstance; class P3dTemplate; }

namespace n2
{

class CompParticle3d;
class RenderParams;

class CompParticle3dInst : public n0::NodeUniqueComp
{
public:
	CompParticle3dInst(const std::shared_ptr<CompParticle3d>& cp3d);

	virtual const char* Type() const override { return TYPE_NAME; }
	virtual n0::UniqueCompID TypeID() const override {
		return n0::GetUniqueCompTypeID<CompParticle3dInst>();
	}
	virtual std::unique_ptr<n0::NodeUniqueComp> Clone(const n0::SceneNode& node) const override;

	bool Update();
	void Draw(const RenderParams& rp) const;

	et::P3dInstance& GetP3dInst() { return *m_p3d_inst; }

	static const char* const TYPE_NAME;

private:
	std::shared_ptr<CompParticle3d> m_cp3d = nullptr;

	std::unique_ptr<et::P3dInstance> m_p3d_inst = nullptr;

}; // CompParticle3dInst

}