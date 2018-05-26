#include "node2/CompAnimInst.h"

#include <anim/AnimInstance.h>
#include <anim/AnimTemplate.h>

namespace n2
{

const char* const CompAnimInst::TYPE_NAME = "n2_anim_inst";

CompAnimInst::CompAnimInst(const std::shared_ptr<anim::AnimTemplate>& anim_temp)
	: m_loop(true)
	, m_interval(0)
	, m_start_random(false)
{
	m_inst = std::make_shared<anim::AnimInstance>(anim_temp);
	anim_temp->AddInstance(m_inst);
}

std::unique_ptr<n0::NodeComp> CompAnimInst::Clone(const n0::SceneNode& node) const
{
	auto& temp = m_inst->GetAnimTemplate();
	auto comp = std::make_unique<CompAnimInst>(temp);
	comp->m_loop         = m_loop;
	comp->m_interval     = m_interval;
	comp->m_start_random = m_start_random;
	comp->m_inst = std::make_shared<anim::AnimInstance>(temp);
	temp->AddInstance(comp->m_inst);
	return comp;
}

bool CompAnimInst::Update()
{
	return m_inst->Update(m_loop, m_interval);
}

bool CompAnimInst::SetFrame(int frame_idx)
{
	return m_inst->SetFrame(frame_idx);
}

void CompAnimInst::TraverseCurrNodes(std::function<bool(const n0::SceneNodePtr&)> func) const
{
	m_inst->TraverseCurrNodes(func);
}

anim::PlayCtrl& CompAnimInst::GetPlayCtrl()
{
	return m_inst->GetPlayCtrl();
}

const anim::PlayCtrl& CompAnimInst::GetPlayCtrl() const
{
	return m_inst->GetPlayCtrl();
}

}