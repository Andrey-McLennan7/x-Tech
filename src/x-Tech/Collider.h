#pragma once
#include "Component.h"

#include <glm/glm.hpp>

namespace xTech
{
	class Collider : public Component
	{
	// Public member functions
	public:

		virtual bool on_collision(const Collider& other) const = 0;
		virtual void get_collision_response(const Collider& other) const = 0;
	};
}