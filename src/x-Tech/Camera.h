#pragma once

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Component.h"

#include <glm/glm.hpp>
#include <memory>

namespace xTech
{
	class Camera : public Component
	{
	// Private data members
	private:

		glm::mat4 m_projection;
		glm::mat4 m_view;

		// Camera Attributes
		glm::vec3 m_front;
		glm::vec3 m_up;
		glm::vec3 m_world_up;
		glm::vec3 m_right;

		// Euler Angles
		float m_yaw;
		float m_pitch;

		// Camera Options
		float m_sensitivity;
		float m_speed;
		float m_zoom;

	// Public member functions
	public:

		Camera(float zoom = 45.0f, float yaw = -90.0f, float pitch = 0.0f);

		void on_tick() override;

		// Process Input
		void mouse_view_movement(float xoffset, float yoffset);

		// Camera transformation matricies
		glm::mat4 projection_matrix() const;
		glm::mat4 view_matrix() const;

		// Setters/Getters
		void yaw(float yaw);
		float yaw() const;

		void pitch(float pitch);
		float pitch() const;

		void sensitivity(float sensitivity);
		float sensitivity() const;

		void speed(float speed);
		float speed() const;

		void zoom(float zoom);
		float zoom() const;
	};
}

#endif