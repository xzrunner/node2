#include "node2/CompImage.h"

namespace n2
{

const char* const CompImage::TYPE_NAME = "n2_image";

//std::unique_ptr<n0::NodeComponent> CompImage::Clone() const
//{
//	auto comp = std::make_unique<CompImage>();
//	comp->m_filepath = m_filepath;
//	// todo clone
//	comp->m_tex = m_tex;
//	return comp;
//}

sm::rect CompImage::GetBounding() const
{
	return sm::rect(
		static_cast<float>(m_tex->GetWidth()), 
		static_cast<float>(m_tex->GetHeight())
	);
}

}