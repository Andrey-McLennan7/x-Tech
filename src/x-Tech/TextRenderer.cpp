#include "TextRenderer.h"

#include "Font.h"
#include "Shader.h"
#include "Camera.h"
#include "Cache.h"

namespace xTech
{
	void TextRenderer::on_initialize()
	{
		this->lock_scale(true);
		this->m_colour = glm::vec3{ 1.0f };
	}

	void TextRenderer::on_display()
	{
		this->m_shader->set_mat4("u_Projection", this->camera()->projection_matrix("ORTHO"));
		this->m_shader->set_vec3("u_TextColour", this->m_colour);

		this->m_font->m_font->draw(this->m_shader->shader(), this->m_text, glm::vec2{ this->position() }, this->scale().x);
	}

	void TextRenderer::font(const std::string& path)
	{
		this->font(this->cache()->load<Font>(path));
	}

	void TextRenderer::font(std::shared_ptr<Font> font)
	{
		this->m_font = font;
	}

	void TextRenderer::shader(const std::string& path)
	{
		this->shader(this->cache()->load<Shader>(path));
	}
	
	void TextRenderer::shader(std::shared_ptr<Shader> shader)
	{
		this->m_shader = shader;
	}

	void TextRenderer::text(const std::string& text)
	{
		this->m_text = text;
	}

	std::string TextRenderer::text() const
	{
		return this->m_text;
	}

	void TextRenderer::colour(const glm::vec3& colour)
	{
		this->m_colour = colour;
	}

	glm::vec3 TextRenderer::colour() const
	{
		return this->m_colour;
	}
}