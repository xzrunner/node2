#include "node2/CompAnim.h"

namespace n2
{

const char* const CompAnim::TYPE_NAME = "n2_anim";

void CompAnim::Traverse(std::function<bool(const n0::SceneNodePtr&)> func, bool inverse) const
{
	//if (inverse)
	//{
	//	for (auto& itr = m_children.rbegin(); itr != m_children.rend(); ++itr) {
	//		if (!func(*itr)) {
	//			break;
	//		}
	//	}
	//}
	//else
	//{
	//	for (auto& child : m_children) {
	//		if (!func(child)) {
	//			break;
	//		}
	//	}
	//}
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

/************************************************************************/
/* class AnimSymbol::Layer                                              */
/************************************************************************/

int CompAnim::Layer::GetCurrFrame(int index) const
{
	if (frames.empty()) {
		return -1;
	}

	int prev = -1, curr = -1;
	int idx = 0;
	for (auto& frame : frames)
	{
		if (frame->index >= index) {
			curr = idx;
			break;
		} else {
			prev = idx;
		}
		++idx;
	}
	
	if (curr < 0) {
		return -1;
	} else if (curr == index) {
		return curr;
	} else if (prev < 0) {
		return -1;
	} else {
		assert(prev <= index);
		return prev;
	}
}

int CompAnim::Layer::GetNextFrame(int index) const
{
	int idx = 0;
	for (auto& frame : frames) {
		if (frame->index > index) {
			return idx;
		}
		++idx;
	}
	return -1;
}

}