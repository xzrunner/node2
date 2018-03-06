#include "node2/CompSprite2.h"

namespace n2
{

const char* const CompSprite2::TYPE_NAME = "n2_sprite2";

//std::unique_ptr<n0::NodeComponent> CompSprite2::Clone() const
//{
//	auto comp = std::make_unique<CompSprite2>();
//	comp->m_filepath = m_filepath;
//	// todo clone
//	comp->m_sym = m_sym;
//	return comp;
//}

sm::rect CompSprite2::GetBounding() const
{
	return sm::rect(100, 100);
}

}