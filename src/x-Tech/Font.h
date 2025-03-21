#pragma once

#ifndef X_TECH_FONT_H
#define X_TECH_FONT_H

#include "Resource.h"
#include <rend/rend.h>

#include <memory>

namespace xTech
{
	class GuiRenderer;
	class Shader;

	class Font : public Resource
	{
	// Public data members
	public:

		std::shared_ptr<rend::Font> m_font;

	// Private member functions
	private:

		virtual void on_load() override;

		void draw(std::shared_ptr<Shader> shader);

		friend class GuiRenderer;
	};
}

#endif