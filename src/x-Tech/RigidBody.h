#pragma once
#include "Component.h"

namespace xTech
{
	class RigidBody : public Component
	{
	// Public member functions
	public:

		virtual void on_tick() override;
	};
}