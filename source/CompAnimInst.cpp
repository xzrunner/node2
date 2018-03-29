#include "node2/CompAnimInst.h"

#include <anim/AnimInstance.h>

namespace n2
{

const char* const CompAnimInst::TYPE_NAME = "n2_anim_inst";

CompAnimInst::CompAnimInst(const std::shared_ptr<const anim::AnimTemplate>& anim_temp)
	: m_loop(true)
	, m_interval(0)
	, m_fps(30)
	, m_start_random(false)
{
	m_inst = std::make_unique<anim::AnimInstance>(anim_temp);
}

std::unique_ptr<n0::NodeUniqueComp> CompAnimInst::Clone(const n0::SceneNode& node) const
{
	auto comp = std::make_unique<CompAnimInst>(m_inst->GetAnimTemplate());
	comp->m_loop         = m_loop;
	comp->m_interval     = m_interval;
	comp->m_fps          = m_fps;
	comp->m_start_random = m_start_random;
	comp->m_inst = std::make_unique<anim::AnimInstance>(*m_inst);
	return comp;
}

bool CompAnimInst::Update()
{
	return m_inst->Update(m_loop, m_interval, m_fps);
}

bool CompAnimInst::SetFrame(int frame_idx)
{
	return m_inst->SetFrame(frame_idx, m_fps);
}

void CompAnimInst::TraverseCurrNodes(std::function<bool(const n0::SceneNodePtr&)> func) const
{
	m_inst->TraverseCurrNodes(func);
}

}