#include "Texture.h"

namespace xTech
{
	void Texture::on_load()
	{
		this->m_texture = std::make_shared<rend::Texture>(this->get_path());
	}
}