#pragma once

#include <node0/CompAsset.h>
#include <node0/typedef.h>

#include <vector>

namespace n2
{

class CompAnim : public n0::CompAsset
{
public:
	class Frame
	{
	public:
		int index;
		std::vector<n0::SceneNodePtr> nodes;

		bool tween;

	public:
		Frame() : index(0), tween(false) {}

	}; // Frame

	using FramePtr = std::unique_ptr<Frame>;

	class Layer
	{
	public:
		std::string name;
		std::vector<FramePtr> frames;

	public:
		int GetCurrFrame(int index) const;
		int GetNextFrame(int index) const;

	}; // Layer

	using LayerPtr = std::unique_ptr<Layer>;

public:
	virtual const char* Type() const override { return TYPE_NAME; }

	virtual n0::AssetID AssetTypeID() const override {
		return n0::GetAssetUniqueTypeID<CompAnim>();
	}
	virtual void Traverse(std::function<bool(const n0::SceneNodePtr&)> func,
		bool inverse = false) const override;
	virtual sm::rect GetBounding() const override;

	void AddLayer(LayerPtr& layer) { m_layers.push_back(std::move(layer)); }

	const std::vector<LayerPtr>& GetAllLayers() const { return m_layers; }

	static const char* const TYPE_NAME;

private:
	std::vector<LayerPtr> m_layers;

}; // CompAnim

}