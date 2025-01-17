#pragma once

#ifndef DEMO_DATA_H
#define DEMO_DATA_H

#include <x-Tech/x-Tech.h>

using namespace xTech;

class Controls;

class Data : public Component
{
	// Private data members
private:

	float m_health;
	float m_distance;

	// Public member functions
public:

	// First to execute when applied
	virtual void on_initialize() override;

	// Executed every iteration
	virtual void on_tick() override;
};

#endif