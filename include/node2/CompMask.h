#pragma once

#include <node0/NodeComponent.h>
#include <node0/typedef.h>

namespace n2
{

class CompMask : public n0::NodeComponent
{
public:
	virtual const char* Type() const override { return TYPE_NAME; }

	void SetBaseNode(const n0::SceneNodePtr& base) { m_base = base; }
	void SetMaskNode(const n0::SceneNodePtr& mask) { m_mask = mask; }
	const n0::SceneNodePtr& GetBaseNode() const { return m_base; }
	const n0::SceneNodePtr& GetMaskNode() const { return m_mask; }

	static const char* const TYPE_NAME;

private:
	n0::SceneNodePtr m_base = nullptr, m_mask = nullptr;

}; // CompMask

}