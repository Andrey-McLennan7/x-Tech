#pragma once

#ifndef DEMO_SHOOT_H
#define DEMO_SHOOT_H

#include <x-Tech/x-Tech.h>

#include <vector>

using namespace xTech;

class Shoot : public Component
{
// Private data members
private:

	std::shared_ptr<Shape> m_model;
	std::vector<std::shared_ptr<Entity>> m_bullets;

// Private member functions
private:

	std::shared_ptr<Entity> generate_bullet_entity();

// Public member functions
public:

	// First to execute when applied
	virtual void on_initialize() override;

	// Executed every iteration
	virtual void on_tick() override;

	void shoot();

};

#endif