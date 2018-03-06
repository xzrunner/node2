#include "node2/CompText.h"

namespace n2
{

const char* const CompText::TYPE_NAME = "n2_text";

//std::unique_ptr<n0::NodeComponent> CompText::Clone() const
//{
//	auto comp = std::make_unique<CompText>();
//	comp->m_text = m_text;
//	return comp;
//}

sm::rect CompText::GetBounding() const
{
	return sm::rect(100, 100);
}

}