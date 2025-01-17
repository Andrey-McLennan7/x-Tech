#pragma once

#ifndef DEMO_COLLISION_RESPONCE_H
#define DEMO_COLLISION_RESPONCE_H

#include <x-Tech/x-Tech.h>

using namespace xTech;

class CollisionResponce : public Component
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