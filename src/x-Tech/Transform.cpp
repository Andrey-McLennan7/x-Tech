#include "Transform.h"
#include "glm/gtc/matrix_transform.hpp"

namespace xTech
{
	void Transform::on_initialize()
	{
		this->m_position = glm::vec3(0.0f);
		this->m_rotation = glm::vec3(0.0f);
		this->m_scale = glm::vec3(1.0f);

		this->m_model_matrix = glm::mat4(1.0f);
	}

	void Transform::on_tick()
	{
		// Update the model matrix
		this->m_model_matrix = glm::translate(glm::mat4(1.0f), this->m_position);
		this->m_model_matrix = glm::rotate(this->m_model_matrix, 1.0f, this->m_rotation);
		this->m_model_matrix = glm::translate(this->m_model_matrix, this->m_scale);
	}
}