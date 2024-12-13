#pragma once

#ifndef X_TECH_INPUT_H
#define X_TECH_INPUT_H

#include <vector>
#include <memory>

namespace xTech
{
	class Core;

	class Input
	{
	// Private data members
	private:

		std::vector<int> m_keys;

		mutable std::vector<int> m_pressed_keys;
		mutable std::vector<int> m_released_keys;

	// Public member functions
	public:

		bool is_key(int key) const;
		bool is_key_pressed(int key) const;
		bool is_key_released(int key) const;

		friend class Core;
	};
}

#endif