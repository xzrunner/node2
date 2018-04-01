#pragma once

#include <node0/NodeUniqueComp.h>
#include <node0/typedef.h>

#include <functional>

namespace anim { class AnimInstance; class AnimTemplate; class PlayCtrl; }

namespace n2
{

class CompAnimInst : public n0::NodeUniqueComp
{
public:
	CompAnimInst(const std::shared_ptr<anim::AnimTemplate>& anim_temp);

	virtual const char* Type() const override { return TYPE_NAME; }
	virtual n0::UniqueCompID TypeID() const override {
		return n0::GetUniqueCompTypeID<CompAnimInst>();
	}
	virtual std::unique_ptr<n0::NodeUniqueComp> Clone(const n0::SceneNode& node) const override;

	bool Update();
	bool SetFrame(int frame_idx);

	void TraverseCurrNodes(std::function<bool(const n0::SceneNodePtr&)> func) const;

	anim::PlayCtrl& GetPlayCtrl();
	const anim::PlayCtrl& GetPlayCtrl() const;

	static const char* const TYPE_NAME;

private:
	bool  m_loop;
	float m_interval;

	bool m_start_random;

	std::shared_ptr<anim::AnimInstance> m_inst = nullptr;

}; // CompAnimInst

}