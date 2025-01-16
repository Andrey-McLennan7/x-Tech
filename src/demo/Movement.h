#pragma once

#ifndef DEMO_MOVEMENT_H
#define DEMO_MOVEMENT_H

#include <x-Tech/Component.h>

using namespace xTech;

class Movement : public Component
{
// Private data members
private:



// Public member functions
public:

	// First to execute when applied
	virtual void on_initialize() override;

	// Executed every iteration
	virtual void on_tick() override;
};

#endif