#pragma once

#include <node0/NodeComponent.h>
#include <sprite2/Symbol.h>

#include <memory>

namespace n2
{

class CompSprite2 : public n0::NodeComponent
{
public:
	virtual const char* Type() const override { return TYPE_NAME; }

	virtual bool StoreToJson(rapidjson::Value& val,
		rapidjson::MemoryPoolAllocator<>& alloc) const override;
	virtual void LoadFromJson(const rapidjson::Value& val) override;

	void SetFilepath(const std::string& filepath) { m_filepath = filepath; }
	const std::string& GetFilepath() const { return m_filepath; }

	void SetSymbol(const s2::SymPtr& sym) { m_sym = sym; }
	const s2::SymPtr& GetSymbol() const { return m_sym; }

	static const char* const TYPE_NAME;

private:
	std::string m_filepath;

	s2::SymPtr m_sym = nullptr;

}; // CompSprite2

}