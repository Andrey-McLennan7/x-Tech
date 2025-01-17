#pragma once

#ifndef DEMO_MOVEMENT_H
#define DEMO_MOVEMENT_H

#include <x-Tech/x-Tech.h>

using namespace xTech;

class Controls;

class Movement : public Component
{
// Private data members
private:

	float m_speed;
	float m_end_point;

// Public member functions
public:

	// First to execute when applied
	virtual void on_initialize() override;

	// Executed every iteration
	virtual void on_tick() override;

	void speed(float speed);
	float speed() const;

	void end_point(float point);
	float end_point() const;
};

#endif