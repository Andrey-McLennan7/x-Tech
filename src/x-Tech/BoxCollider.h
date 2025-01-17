#pragma once

#ifndef X_TECH_BOX_COLLIDER_H
#define X_TECH_BOX_COLLIDER_H

#include "Collider.h"

#include <glm/glm.hpp>

namespace xTech
{
	class BoxCollider : public Collider
	{
	// Private data members
	private:

		glm::vec3 m_size;
		glm::vec3 m_offset;

	// Public member functions
	public:

		virtual void on_initialize() override;

		virtual bool on_collision(const Collider& other) const override;
		virtual void get_collision_response(const Collider& other) const override;

		void size(const glm::vec3& size);
		void size(float size);
	};
}

#endif