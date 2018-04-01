#include "node2/CompParticle3dInst.h"
#include "node2/CompParticle3d.h"
#include "node2/RenderSystem.h"

#include <emitter/P3dInstance.h>
#include <emitter/P3dRenderParams.h>

namespace n2
{

const char* const CompParticle3dInst::TYPE_NAME = "n2_particle3d_inst";

CompParticle3dInst::CompParticle3dInst(const std::shared_ptr<CompParticle3d>& cp3d)
	: m_cp3d(cp3d)
{
	m_p3d_inst = std::make_unique<et::P3dInstance>(cp3d->GetP3DTemp());
}

std::unique_ptr<n0::NodeUniqueComp> CompParticle3dInst::Clone(const n0::SceneNode& node) const
{
	auto comp = std::make_unique<CompParticle3dInst>(m_cp3d);
	return comp;
}

bool CompParticle3dInst::Update()
{
	return m_p3d_inst->Update();
}

void CompParticle3dInst::Draw(const RenderParams& rp) const
{
	et::P3dRenderParams p3d_rp;
	p3d_rp.mat = rp.GetMatrix();
	p3d_rp.col = rp.GetColor();
	p3d_rp.local = m_p3d_inst->IsLocal();

	m_p3d_inst->Draw(p3d_rp, false);
}

}