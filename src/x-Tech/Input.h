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

		std::vector<int> m_m_buttons;
		mutable std::vector<int> m_pressed_mouse_buttons;
		mutable std::vector<int> m_released_mouse_buttons;

		std::vector<int> m_controller_buttons;
		mutable std::vector<int> m_pressed_controller_buttons;
		mutable std::vector<int> m_released_controller_buttons;

		glm::ivec2 m_cursor;
		bool m_mouse_motion;
		int m_wheel;

		glm::ivec2 m_joy_stick_direction;
		bool m_invert_x;
		bool m_invert_y;
		int m_dead_zone;

	// Public member functions
	public:

		Input(int dead_zone = 8000);

		bool is_key(int key) const;
		bool is_key_pressed(int key) const;
		bool is_key_released(int key) const;

		bool is_mouse_button(int button) const;
		bool is_mouse_button_pressed(int button) const;
		bool is_mouse_button_released(int button) const;

		bool is_controller_button(int button) const;
		bool is_controller_button_pressed(int button) const;
		bool is_controller_button_released(int button) const;

		glm::ivec2 cursor() const;
		int cursor_x() const;
		int cursor_y() const;
		int wheel() const;

		bool mouse_in_motion() const;

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
	};
}

#endif