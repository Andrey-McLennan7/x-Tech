#include "Transform.h"
#include "glm/gtc/matrix_transform.hpp"

namespace xTech
{
	void Transform::on_initialize()
	{
		this->m_position = glm::vec3{ 0.0f };
		this->m_rotation = glm::vec3{ 0.0f };
		this->m_scale = glm::vec3{ 1.0f };
	}

	glm::mat4 Transform::model_matrix()
	{
		// Update the model matrix
		glm::mat4 rtn;

		rtn = glm::translate(glm::mat4(1.0f), this->m_position);

		rtn = glm::rotate(rtn, this->m_rotation.y, glm::vec3{ 0.0f, 1.0f, 0.0f });
		rtn = glm::rotate(rtn, this->m_rotation.x, glm::vec3{ 1.0f, 0.0f, 0.0f });
		rtn = glm::rotate(rtn, this->m_rotation.z, glm::vec3{ 0.0f, 0.0f, 1.0f });

		rtn = glm::scale(rtn, this->m_scale);

		return rtn;
	}

	void Transform::move(const glm::vec3& move)
	{
		this->m_position += move;
	}

	void Transform::position(const glm::vec3& position)
	{
		this->m_position = position;
	}

	void Transform::rotation(const glm::vec3& rotation)
	{
		this->m_rotation = rotation;
	}

	void Transform::scale(const glm::vec3& scale)
	{
		this->m_scale = scale;
	}

	glm::vec3 Transform::position() const
	{
		return this->m_position;
	}

	glm::vec3 Transform::rotation() const
	{
		return this->m_rotation;
	}

	glm::vec3 Transform::scale() const
	{
		return this->m_scale;
	}
}