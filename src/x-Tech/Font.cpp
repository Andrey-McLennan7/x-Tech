#include "Font.h"

namespace xTech
{
	void xTech::Font::on_load()
	{
		this->m_font = std::make_shared<rend::Font>(this->get_path() + ".ttf");
	}
}