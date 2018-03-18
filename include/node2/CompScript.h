#pragma once

#include <node0/NodeUniqueComp.h>
#include <node0/typedef.h>
#include <dust/SceneNodeScript.h>

#include <string>

namespace n2
{

class CompScript : public n0::NodeUniqueComp
{
public:
	virtual const char* Type() const override { return TYPE_NAME; }
	virtual n0::UniqueCompID TypeID() const override {
		return n0::GetUniqueCompTypeID<CompScript>(); 
	}
	virtual std::unique_ptr<n0::NodeUniqueComp> Clone(const n0::SceneNode& node) const override;

	const std::string& GetFilepath() const { return m_filepath; }
	void SetFilepath(const std::string& filepath, const n0::SceneNodePtr& node);

	void Update() const { m_script.OnUpdate(); }
	void Draw() const { m_script.OnDraw(); }

	void Reload();

	static const char* const TYPE_NAME;

private:
	std::string m_filepath;

	dust::SceneNodeScript m_script;

}; // CompScript

}