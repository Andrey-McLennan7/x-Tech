#pragma once

#ifndef X_TECH_KEYBOARD_H
#define X_TECH_KEYBOARD_H

#include "InputDevice.h"

namespace xTech
{
	class Core;
	class Input;

	class Keyboard : public InputDevice
	{
	// Private data members
	private:



	// Public member functions
	public:

		friend class Core;
		friend class Input;
	};
}

#endif