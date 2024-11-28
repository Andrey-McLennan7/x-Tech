#pragma once
#include "Component.h"

#include <vector>
#include <memory>

namespace xTech
{
	class Collider;

	class RigidBody : public Component
	{
	// Private data member
	private:

		std::vector<std::shared_ptr<Collider>> m_colliders;

	// Public member functions
	public:

		virtual void on_tick() override;
	};
}