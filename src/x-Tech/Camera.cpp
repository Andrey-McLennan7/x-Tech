#include "Camera.h"
#include "Transform.h"
#include "Core.h"
#include "Window.h"

#include <glm/gtc/matrix_transform.hpp>

namespace xTech
{
	Camera::Camera(float zoom, float yaw, float pitch) :
		m_zoom{ zoom }, m_yaw{ yaw }, m_pitch{ pitch },

		m_speed{ 2.5f },
		m_front{ glm::vec3{ 0.0f, 0.0f, -1.0f } },
		m_sensitivity{ 0.1f },
		m_up{ glm::vec3{ 0.0f } },
		m_right{ glm::vec3{ 0.0f } },
		m_world_up{ glm::vec3{ 0.0f, 1.0f, 0.0f } },

		m_projection{ glm::mat4{ 1.0f } },
		m_view{ glm::mat4{ 1.0f } }
	{}

	void Camera::on_tick()
	{
		// Recalculate View Direction
		glm::vec3 direction
		{
			std::cos(glm::radians(this->m_yaw)) * std::cos(glm::radians(this->m_pitch)),
			std::sin(glm::radians(this->m_pitch)),
			std::sin(glm::radians(this->m_yaw)) * std::cos(glm::radians(this->m_pitch))
		};

		// Set new front
		this->m_front = glm::normalize(direction);

		// Recalculate right and up vectors
		this->m_right = glm::normalize(glm::cross(this->m_front, this->m_world_up));
		this->m_up = glm::normalize(glm::cross(this->m_right, this->m_front));

		// Update camera matrcies
		float height{ (float)this->core()->window()->size().y };
		float width{ (float)this->core()->window()->size().x };

		this->m_projection = glm::perspective(this->m_zoom, width / height, 0.1f, 100.0f);
		this->m_view = glm::lookAt(this->transform()->position(), this->transform()->position() + this->m_front, this->m_up);
	}

	void Camera::mouse_view_movement(float xoffset, float yoffset)
	{
		xoffset *= this->m_sensitivity;
		yoffset *= this->m_sensitivity;

		this->m_yaw += xoffset;
		this->m_pitch += yoffset;

		if (this->m_pitch >= 89.0f)
			this->m_pitch = 89.0f;

		if (this->m_pitch <= -89.0f)
			this->m_pitch = -89.0f;
	}

	glm::mat4 Camera::projection_matrix() const
	{
		// Update camera matrcies
		float height{ (float)this->core()->window()->size().y };
		float width{ (float)this->core()->window()->size().x };

		return glm::perspective(this->m_zoom, width / height, 0.1f, 100.0f);
	}

	glm::mat4 Camera::view_matrix() const
	{
		return this->m_view;
	}

	void Camera::yaw(float yaw)
	{
		this->m_yaw = yaw;
	}

	float Camera::yaw() const
	{
		return this->m_yaw;
	}

	void Camera::pitch(float pitch)
	{
		this->m_pitch = pitch;
	}

	float Camera::pitch() const
	{
		return this->m_pitch;
	}

	void Camera::sensitivity(float sensitivity)
	{
		this->m_sensitivity = sensitivity;
	}

	float Camera::sensitivity() const
	{
		return this->m_sensitivity;
	}

	void Camera::speed(float speed)
	{
		this->m_speed = speed;
	}

	float Camera::speed() const
	{
		return this->m_speed;
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