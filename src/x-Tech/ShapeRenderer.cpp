#include "ShapeRenderer.h"

#include "Shape.h"
#include "Shader.h"

#include <stdexcept>

namespace xTech
{
	void ShapeRenderer::on_initialize()
	{
		this->m_colour = glm::vec3{ 1.0f };
	}

	void ShapeRenderer::on_tick()
	{
		if (this->m_shader)
		{
			this->m_shader->set_vec3("u_Colour", this->m_colour);
		}
	}

	void ShapeRenderer::on_display()
	{
		if (!this->m_shader)
		{
			throw std::runtime_error("ERROR::NO SHADERS FOUND");
		}

		this->m_shape->draw(this->m_shader);
	}

	void ShapeRenderer::shader(std::shared_ptr<Shader> shader)
	{
		this->m_shader = shader;
	}

	void ShapeRenderer::shape(std::shared_ptr<Shape> shape)
	{
		this->m_shape = shape;
	}

	void ShapeRenderer::colour(const glm::vec3& colour)
	{
		this->m_colour = colour;
	}

	glm::vec3 ShapeRenderer::colour() const
	{
		return this->m_colour;
	}
}