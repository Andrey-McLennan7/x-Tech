#pragma once

#ifndef X_TECH_INPUT_H
#define X_TECH_INPUT_H

#include <vector>
#include <memory>

#include <glm/glm.hpp>

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

		std::vector<int> m_buttons;
		mutable std::vector<int> m_pressed_buttons;
		mutable std::vector<int> m_released_buttons;

		glm::ivec2 m_cursor;
		bool m_motion;
		int m_wheel;

	// Public member functions
	public:

		bool is_key(int key) const;
		bool is_key_pressed(int key) const;
		bool is_key_released(int key) const;

		bool is_button(int button) const;
		bool is_button_pressed(int button) const;
		bool is_button_released(int button) const;

		glm::ivec2 cursor() const;
		int cursor_x() const;
		int cursor_y() const;
		int wheel() const;

		bool in_motion() const;

		friend class Core;
	};
}

#endif