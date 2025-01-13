#include "Controller.h"

#include <iostream>

namespace xTech
{
	Controller::Controller(int dead_zone) :
		m_id{ nullptr },
		m_joy_stick_direction{ glm::ivec2{ 0 } },
		m_invert_x{ false },
		m_invert_y{ true },
		m_dead_zone{ dead_zone }
	{}

	glm::ivec2 Controller::joy_stick_direction() const
	{
		return this->m_joy_stick_direction;
	}

	int Controller::joy_stick_direction_x() const
	{
		return this->m_joy_stick_direction.x;
	}

	int Controller::joy_stick_direction_y() const
	{
		return this->m_joy_stick_direction.y;
	}

	void Controller::dead_zone(int dead_zone)
	{
		this->m_dead_zone = dead_zone;
	}

	int Controller::dead_zone() const
	{
		return this->m_dead_zone;
	}

	void Controller::invert_x(bool invert)
	{
		this->m_invert_x = invert;
	}

	bool Controller::invert_x() const
	{
		return this->m_invert_x;
	}

	void Controller::invert_y(bool invert)
	{
		this->m_invert_y = invert;
	}

	bool Controller::invert_y() const
	{
		return this->m_invert_y;
	}
}