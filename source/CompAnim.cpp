#include "node2/CompAnim.h"
#include "node2/AABBSystem.h"

#include <guard/check.h>
#include <anim/KeyFrame.h>
#include <anim/Layer.h>
#include <anim/AnimTemplate.h>

namespace n2
{

const char* const CompAnim::TYPE_NAME = "n2_anim";

CompAnim::CompAnim()
	: m_fps(30)
{
	m_anim_temp = std::make_shared<anim::AnimTemplate>();
}

void CompAnim::Traverse(std::function<bool(const n0::SceneNodePtr&)> func, bool inverse) const
{
	GD_ASSERT(m_anim_temp, "err temp");
	auto& slots = m_anim_temp->GetAllSlots();
	if (inverse)
	{
		for (auto& itr = slots.rbegin(); itr != slots.rend(); ++itr) {
			if (!func(*itr)) {
				break;
			}
		}
	}
	else
	{
		for (auto& node : slots) {
			if (!func(node)) {
				break;
			}
		}
	}
}

void CompAnim::AddLayer(anim::LayerPtr& layer) 
{ 
	m_layers.push_back(std::move(layer)); 
}

void CompAnim::SwapLayers(int idx0, int idx1) 
{
	std::iter_swap(m_layers.begin() + idx0, m_layers.begin() + idx1);
}

bool CompAnim::RemoveAllLayers() 
{ 
	bool dirty = !m_layers.empty();
	m_layers.clear(); 
	return dirty;
}

}