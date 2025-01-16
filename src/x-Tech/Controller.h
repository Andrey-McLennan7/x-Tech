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

		int m_id;

		glm::ivec2 m_left_analogue;
		glm::ivec2 m_right_analogue;

		int m_dead_zone;

		bool m_invert_x;
		bool m_invert_y;

	public:

		Controller(int dead_zone = 8000);

		glm::ivec2 left_analogue() const;
		glm::ivec2 right_analogue() const;

		int left_analogue_x() const;
		int left_analogue_y() const;

		int right_analogue_x() const;
		int right_analogue_y() const;

		bool left_analogue_in_motion() const;
		bool right_analogue_in_motion() const;

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