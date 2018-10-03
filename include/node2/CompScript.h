#pragma once

#include <node0/NodeComp.h>
#include <node0/typedef.h>
#include <moon/SceneNodeScript.h>

#include <string>

namespace n2
{

class CompScript : public n0::NodeComp
{
public:
	virtual const char* Type() const override { return TYPE_NAME; }
	virtual n0::CompID TypeID() const override {
		return n0::GetCompTypeID<CompScript>();
	}
	virtual std::unique_ptr<n0::NodeComp> Clone(const n0::SceneNode& node) const override;

	const std::string& GetFilepath() const { return m_filepath; }
	void SetFilepath(const std::string& filepath) { m_filepath = filepath; }

	void Init() const   { m_script.Init(); }
	void Update() const { m_script.Update(); }
	void Draw() const   { m_script.Draw(); }

	void Reload(const n0::SceneNodePtr& node);

	static const char* const TYPE_NAME;

private:
	std::string m_filepath;

	moon::SceneNodeScript m_script;

}; // CompScript

}