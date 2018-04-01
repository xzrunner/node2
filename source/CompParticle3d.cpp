#include "node2/CompParticle3d.h"

#include <emitter/P3dTemplate.h>

namespace n2
{

const char* const CompParticle3d::TYPE_NAME = "n2_particle3d";

CompParticle3d::CompParticle3d(int max_sym_count)
{
	m_p3d_temp = std::make_unique<et::P3dTemplate>(max_sym_count);
}

void CompParticle3d::Traverse(std::function<bool(const n0::SceneNodePtr&)> func, bool inverse) const
{

}

sm::rect CompParticle3d::GetBounding() const
{
	return sm::rect(100, 100);
}

}