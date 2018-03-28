#pragma once

#include <node0/CompAsset.h>
#include <anim/typedef.h>
#include <anim/PlayCtrl.h>

#include <vector>

namespace n2
{

class CompAnim : public n0::CompAsset
{
public:
	CompAnim();

	virtual const char* Type() const override { return TYPE_NAME; }

	virtual n0::AssetID AssetTypeID() const override {
		return n0::GetAssetUniqueTypeID<CompAnim>();
	}
	virtual void Traverse(std::function<bool(const n0::SceneNodePtr&)> func,
		bool inverse = false) const override;
	virtual sm::rect GetBounding() const override;

	void AddLayer(anim::LayerPtr& layer);
	void SwapLayers(int idx0, int idx1);
	bool RemoveAllLayers();

	const std::vector<anim::LayerPtr>& GetAllLayers() const { return m_layers; }

	const anim::PlayCtrl& GetPlayCtrl() const { return m_ctrl; }
	anim::PlayCtrl& GetPlayCtrl() { return m_ctrl; }

	uint32_t GetFPS() const { return m_fps; }

	int GetMaxFrame() const;

	static const char* const TYPE_NAME;

private:
	std::vector<anim::LayerPtr> m_layers;

	anim::PlayCtrl m_ctrl;

	uint32_t m_fps;
	
}; // CompAnim

}