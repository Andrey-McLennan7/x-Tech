#pragma once

#ifndef DEMO_CONTROLS_H
#define DEMO_CONTROLS_H

#include <x-Tech/x-Tech.h>

using namespace xTech;

class Movement;

class Controls : public Component
{
// Private data members
private:

	float m_speed;

	std::shared_ptr<SoundSource> m_sound;

// Public member functions
public:

	// First to execute when applied
	virtual void on_initialize() override;

	// Executed every iteration
	virtual void on_tick() override;

	friend class Movement;
};

#endif