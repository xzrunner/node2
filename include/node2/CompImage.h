#pragma once

#include <node0/NodeComponent.h>
#include <painting2/Texture.h>

#include <memory>

namespace n2
{

class CompImage : public n0::NodeComponent
{
public:
	virtual const char* Type() const override { return TYPE_NAME; }
	virtual n0::ComponentID TypeID() const override { 
		return n0::GetComponentTypeID<CompImage>(); }
	virtual std::unique_ptr<n0::NodeComponent> Clone() const override;

	void SetFilepath(const std::string& filepath) { m_filepath = filepath; }
	const std::string& GetFilepath() const { return m_filepath; }

	void SetTexture(const std::shared_ptr<pt2::Texture>& tex) { m_tex = tex; }
	const std::shared_ptr<pt2::Texture>& GetTexture() const { return m_tex; }

	static const char* const TYPE_NAME;

private:
	std::string m_filepath;

	std::shared_ptr<pt2::Texture> m_tex = nullptr;

}; // CompImage

}