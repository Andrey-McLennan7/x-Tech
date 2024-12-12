#pragma once

#ifndef X_TECH_RIGID_BODY_H
#define X_TECH_RIGID_BODY_H

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

#endif