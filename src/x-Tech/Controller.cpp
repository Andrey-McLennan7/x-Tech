#include "Controller.h"

#include <iostream>

namespace xTech
{
	Controller::Controller(int dead_zone) :
		m_id{ 0 },
		m_left_analogue{ glm::ivec2{ 0 } },
		m_right_analogue{ glm::ivec2{ 0 } },
		m_invert_x{ false },
		m_invert_y{ true },
		m_dead_zone{ dead_zone }
	{}

	glm::ivec2 Controller::left_analogue() const
	{
		return this->m_left_analogue;
	}

	glm::ivec2 Controller::right_analogue() const
	{
		return this->m_right_analogue;
	}

	int Controller::left_analogue_x() const
	{
		return this->m_left_analogue.x;
	}

	int Controller::left_analogue_y() const
	{
		return this->m_left_analogue.y;
	}

	int Controller::right_analogue_x() const
	{
		return this->m_right_analogue.x;
	}

	int Controller::right_analogue_y() const
	{
		return this->m_right_analogue.y;
	}

	bool Controller::left_analogue_in_motion() const
	{
		return (this->m_left_analogue != glm::ivec2{ 0 });
	}

	bool Controller::right_analogue_in_motion() const
	{
		return (this->m_right_analogue != glm::ivec2{ 0 });
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