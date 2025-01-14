#include "2DGuiRenderer.h"

#include "Font.h"
#include "Shader.h"
#include "Camera.h"

namespace xTech
{
	void GuiRenderer2D::on_initialize()
	{
		this->lock_scale(true);
	}

	void GuiRenderer2D::on_display()
	{
		this->m_shader->set_mat4("u_Projection", this->camera()->projection_matrix("ORTHO"));
		this->m_shader->set_vec3("u_TextColour", glm::vec3{ 191.0f / 255.0f });

		this->m_font->m_font->draw(this->m_shader->shader(), this->m_text, glm::vec2{ this->position() }, this->scale().x);
	}

	void GuiRenderer2D::font(std::shared_ptr<Font> font)
	{
		this->m_font = font;
	}

	void GuiRenderer2D::shader(std::shared_ptr<Shader> shader)
	{
		this->m_shader = shader;
	}

	void GuiRenderer2D::text(const std::string& text)
	{
		this->m_text = text;
	}

	std::string GuiRenderer2D::text() const
	{
		return this->m_text;
	}
}