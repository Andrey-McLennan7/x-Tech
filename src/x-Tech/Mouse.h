#pragma once

#ifndef X_TECH_MOUSE_H
#define X_TECH_MOUSE_H

#include "InputDevice.h"

#include <glm/glm.hpp>

namespace xTech
{
	class Core;
	class Input;

	class Mouse : public InputDevice
	{
	// Private data members
	private:

		glm::ivec2 m_cursor;
		bool m_in_motion;
		int m_wheel;

	// Public member functions
	public:

		Mouse();

		glm::ivec2 cursor() const;

		int cursor_x() const;
		int cursor_y() const;
		int wheel() const;

		bool in_motion() const;

		friend class Core;
		friend class Input;
	};
}

#endif