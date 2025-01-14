#pragma once

#ifndef X_TECH_TRANSFORM_H
#define X_TECH_TRANSFORM_H

#include "Component.h"
#include <glm/glm.hpp>

namespace xTech
{
	class Transform : public Component
	{
	// Private data members
	private:

		glm::vec3 m_position;
		glm::vec3 m_rotation;
		glm::vec3 m_scale;

		bool m_lock_scale;

	// Public member functions
	public:

		virtual void on_initialize() override;

		glm::mat4 model_matrix();

		void move(const glm::vec3& move);

		void position(const glm::vec3& position);
		glm::vec3 position() const;

		void rotation(const glm::vec3& rotation);
		glm::vec3 rotation() const;

		void scale(const glm::vec3& scale);
		void scale(float scale);
		glm::vec3 scale() const;

		void lock_scale(bool lock);
	};
}

#endif