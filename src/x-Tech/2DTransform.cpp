#include "2DTransform.h"

#include "Window.h"

namespace xTech
{
	void Transform2D::on_initialize()
	{
		this->m_position = glm::vec2{ (glm::vec2)this->window()->size() / 2.0f };
		this->m_rotation = 0.0f;
		this->m_scale = 1.0f;
	}

	void Transform2D::move(const glm::vec2& move)
	{
		this->m_position += move;
	}

	void Transform2D::position(const glm::vec2& position)
	{
		this->m_position = position;
	}

	glm::vec2 Transform2D::position() const
	{
		return this->m_position;
	}

	void Transform2D::rotation(float rotation)
	{
		this->m_rotation = rotation;
	}

	float Transform2D::rotation() const
	{
		return this->m_rotation;
	}

	void Transform2D::scale(float scale)
	{
		this->m_scale = scale;
	}

	float Transform2D::scale() const
	{
		return this->m_scale;
	}
}