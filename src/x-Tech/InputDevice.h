#pragma once

#ifndef X_TECH_INPUT_DEVICE_H
#define X_TECH_INPUT_DEVICE_H

#include <vector>

namespace xTech
{
	class Core;
	class Input;

	class InputDevice
	{
	// Private data members
	private:

		std::vector<int> m_is;
		mutable std::vector<int> m_is_pressed;
		mutable std::vector<int> m_is_released;

	// Public member functions
	public:

		bool is(int input);
		bool is_pressed(int input);
		bool is_released(int input);

		friend class Core;
		friend class Input;
	};
}

#endif