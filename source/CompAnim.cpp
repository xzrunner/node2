#include "node2/CompAnim.h"

#include <anim/KeyFrame.h>
#include <anim/Layer.h>

namespace n2
{

const char* const CompAnim::TYPE_NAME = "n2_anim";

void CompAnim::Traverse(std::function<bool(const n0::SceneNodePtr&)> func, bool inverse) const
{
	auto& layers = GetAllLayers();
	int frame_idx = m_ctrl.GetFrame();
	for (auto& layer : layers)
	{
		auto frame = layer->GetCurrKeyFrame(frame_idx);
		if (frame)
		{
			auto& nodes = frame->GetAllNodes();

			if (inverse)
			{
				for (auto& itr = nodes.rbegin(); itr != nodes.rend(); ++itr) {
					if (!func(*itr)) {
						break;
					}
				}
			}
			else
			{
				for (auto& node : nodes) {
					if (!func(node)) {
						break;
					}
				}
			}
		}
	}
}

sm::rect CompAnim::GetBounding() const
{
	//sm::rect aabb;
	//for (auto& child : m_children) {
	//	AABBHelper::Combine(aabb, child);
	//}
	//return aabb;

	return sm::rect(100, 100);
}

void CompAnim::AddLayer(anim::LayerPtr& layer) 
{ 
	m_layers.push_back(std::move(layer)); 
}

void CompAnim::SwapLayers(int idx0, int idx1) 
{
	std::iter_swap(m_layers.begin() + idx0, m_layers.begin() + idx1);
}

//int CompAnim::GetCurrFrameIdx() const
//{
//	return m_ctrl.GetFrame();
//}

void CompAnim::SetCurrFrameIdx(int frame)
{
	m_ctrl.SetFrame(frame);
}

}