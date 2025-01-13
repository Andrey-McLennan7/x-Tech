#include "Camera.h"
#include "Transform.h"
#include "Core.h"
#include "Window.h"

#include <glm/gtc/matrix_transform.hpp>

#include <vector>

namespace xTech
{
	void Camera::on_initialize()
	{
		this->m_zoom = 45.0f;

		this->core()->m_cameras.push_back(this->entity()->get_component<Camera>());
	}

	glm::mat4 Camera::projection_matrix() const
	{
		float height{ (float)this->core()->window()->size().y };
		float width{ (float)this->core()->window()->size().x };

		return glm::perspective(this->m_zoom, width / height, 0.1f, 100.0f);
	}

	glm::mat4 Camera::view_matrix() const
	{
		return glm::inverse(this->transform()->model_matrix());
	}

	void Camera::zoom(float zoom)
	{
		this->m_zoom = zoom;
	}

	float Camera::zoom() const
	{
		return this->m_zoom;
	}
}