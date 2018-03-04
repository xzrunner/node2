#pragma once

#include <node0/NodeComponent.h>
#include <painting2/Text.h>

namespace n2
{

class CompText : public n0::NodeComponent
{
public:
	virtual const char* Type() const override { return TYPE_NAME; }
	virtual n0::ComponentID TypeID() const override { 
		return n0::GetComponentTypeID<CompText>(); }
	virtual std::unique_ptr<n0::NodeComponent> Clone() const override;

	const pt2::Text& GetText() const { return m_text; }
	pt2::Text& GetText() { return m_text; }

	void SetText(const pt2::Text& text) { m_text = text; }

	static const char* const TYPE_NAME;

private:
	pt2::Text m_text;

}; // CompText

}