#include "ShapeRenderer.h"

#include "Core.h"
#include "Shape.h"
#include "Shader.h"
#include "Transform.h"
#include "Camera.h"

#include <stdexcept>

namespace xTech
{
	void ShapeRenderer::on_initialize()
	{
		this->m_colour = glm::vec3{ 1.0f };
	}

	void ShapeRenderer::on_display()
	{
		if (!this->m_shader)
		{
			throw std::runtime_error("ERROR::NO SHADERS FOUND");
		}

		// Vertex shader
		this->m_shader->set_mat4("u_Projection", this->core()->current_camera()->projection_matrix());
		this->m_shader->set_mat4("u_View", this->core()->current_camera()->view_matrix());
		this->m_shader->set_mat4("u_Model", this->transform()->model_matrix());

		// Fragment shader
		this->m_shader->set_vec3("u_Colour", this->m_colour);

		this->m_shape->m_shape->draw(this->m_shader->shader());
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
		this->m_colour = colour / 255.0f;
	}

	glm::vec3 ShapeRenderer::colour() const
	{
		return this->m_colour;
	}
}