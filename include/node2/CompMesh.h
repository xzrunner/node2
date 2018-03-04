#pragma once

#include <node0/NodeComponent.h>
#include <node0/typedef.h>

#include <painting2/Mesh.h>

namespace n2
{

class CompMesh : public n0::NodeComponent
{
public:
	virtual const char* Type() const override { return TYPE_NAME; }
	virtual n0::ComponentID TypeID() const override { 
		return n0::GetComponentTypeID<CompMesh>(); }
	virtual std::unique_ptr<n0::NodeComponent> Clone() const override;

	const std::unique_ptr<pt2::Mesh<n0::SceneNode>>& GetMesh() const { return m_mesh; }
	std::unique_ptr<pt2::Mesh<n0::SceneNode>>& GetMesh() { return m_mesh; }
	void SetMesh(std::unique_ptr<pt2::Mesh<n0::SceneNode>>& mesh) { m_mesh = std::move(mesh); }

	static const char* const TYPE_NAME;

private:
	std::unique_ptr<pt2::Mesh<n0::SceneNode>> m_mesh = nullptr;

}; // CompMesh

}