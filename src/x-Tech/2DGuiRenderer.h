#pragma once

#ifndef X_TECH_GUI_RENDERER_H
#define X_TECH_GUI_RENDERER_H

#include "Component.h"

#include <memory>
#include <vector>
#include <string>

namespace xTech
{
	class Font;
	class Shader;

	class GuiRenderer2D : public Component
	{
	// Private data members
	private:

		std::shared_ptr<Font> m_font;
		std::shared_ptr<Shader> m_shader;

		std::string m_text;

	// Public member functions
	public:

		virtual void on_initialize() override;
		virtual void on_display() override;

		void font(std::shared_ptr<Font> font);
		void shader(std::shared_ptr<Shader> shader);

		void text(const std::string& text);
		std::string text() const;
	};
}

#endif