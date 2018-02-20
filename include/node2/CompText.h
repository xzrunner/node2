#pragma once

#include <node0/NodeComponent.h>
#include <painting2/Text.h>

namespace n2
{

class CompText : public n0::NodeComponent
{
public:
	virtual const char* Type() const override { return TYPE_NAME; }

	virtual bool StoreToJson(rapidjson::Value& val,
		rapidjson::MemoryPoolAllocator<>& alloc) const override;
	virtual void LoadFromJson(const rapidjson::Value& val) override;

	const pt2::Text& GetText() const { return m_text; }
	pt2::Text& GetText() { return m_text; }

	static const char* const TYPE_NAME;

private:
	pt2::Text m_text;

}; // CompText

}