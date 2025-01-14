#pragma once

#ifndef X_TECH_CAMERA_H
#define X_TECH_CAMERA_H

#include "Component.h"

#include <glm/glm.hpp>

#include <memory>
#include <string>

namespace xTech
{
	class Camera : public Component
	{
	// Private data members
	private:

		// Camera Options
		float m_zoom;

	// Public member functions
	public:

		virtual void on_initialize() override;

		// Camera transformation matricies
		glm::mat4 projection_matrix(const std::string& type = "PERSPECTIVE") const;
		glm::mat4 view_matrix() const;

		// Camera options
		void zoom(float zoom);
		float zoom() const;
	};
}

#endif