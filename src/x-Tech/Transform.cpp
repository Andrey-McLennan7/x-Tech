#include "Transform.h"
#include "glm/gtc/matrix_transform.hpp"

namespace xTech
{
	void Transform::on_initialize()
	{
		this->m_position = glm::vec3(0.0f);
		this->m_rotation = glm::vec3(0.0f);
		this->m_scale = glm::vec3(1.0f);
	}

	glm::mat4 Transform::get_model_matrix()
	{
		// Update the model matrix
		glm::mat4 rtn;

		rtn = glm::translate(glm::mat4(1.0f), this->m_position);

		rtn = glm::rotate(rtn, this->m_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
		rtn = glm::rotate(rtn, this->m_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		rtn = glm::rotate(rtn, this->m_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

		rtn = glm::scale(rtn, this->m_scale);

		return rtn;
	}

	void Transform::on_tick()
	{

	}
}