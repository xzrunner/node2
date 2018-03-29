#pragma once

#include <node0/NodeUniqueComp.h>
#include <anim/AnimInstance.h>

namespace n2
{

class CompAnimInst : public n0::NodeUniqueComp
{
public:
	CompAnimInst(const std::shared_ptr<const anim::AnimTemplate>& anim_temp);

	virtual const char* Type() const override { return TYPE_NAME; }
	virtual n0::UniqueCompID TypeID() const override {
		return n0::GetUniqueCompTypeID<CompAnimInst>();
	}
	virtual std::unique_ptr<n0::NodeUniqueComp> Clone(const n0::SceneNode& node) const override;

	void Refresh();

	bool Update();
	bool SetFrame(int frame_idx);

	void TraverseCurrNodes(std::function<bool(const n0::SceneNodePtr&)> func) const;

	anim::PlayCtrl& GetPlayCtrl();
	const anim::PlayCtrl& GetPlayCtrl() const;

	static const char* const TYPE_NAME;

private:
	bool  m_loop;
	float m_interval;

	int m_fps;

	bool m_start_random;

	std::unique_ptr<anim::AnimInstance> m_inst = nullptr;

}; // CompAnimInst

}