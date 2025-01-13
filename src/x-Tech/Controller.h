#pragma once

#ifndef X_TECH_CONTROLLER_H
#define X_TECH_CONTROLLER_H

#include "InputDevice.h"

#include <SDL2/SDL_joystick.h>
#include <glm/glm.hpp>

#include <vector>

namespace xTech
{
	class Core;
	class Input;

	class Controller : public InputDevice
	{
	private:

		SDL_Joystick* m_id;

		glm::ivec2 m_joy_stick_direction;

		int m_dead_zone;

		bool m_invert_x;
		bool m_invert_y;

	public:

		Controller(int dead_zone = 8000);

		glm::ivec2 joy_stick_direction() const;

		int joy_stick_direction_x() const;
		int joy_stick_direction_y() const;

		void dead_zone(int dead_zone);
		int dead_zone() const;

		void invert_x(bool invert);
		bool invert_x() const;

		void invert_y(bool invert);
		bool invert_y() const;

		friend class Core;
		friend class Input;
	};
}

#endif