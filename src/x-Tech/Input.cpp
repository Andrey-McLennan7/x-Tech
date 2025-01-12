#include "Input.h"

#include <SDL2/SDL_joystick.h>

#include <iostream>

namespace xTech
{
	Input::Input(int dead_zone) :
		m_dead_zone{ dead_zone },
		m_mouse_motion{ false },
		m_wheel{ 0 },
		m_cursor{ 0 },
		m_joy_stick_direction{ glm::ivec2{ 0 } },
		m_invert_x{ false },
		m_invert_y{ true }
	{
		SDL_Joystick* joy_stick{ nullptr };

		if (SDL_NumJoysticks() < 1)
		{
			std::cout << "No joystick available" << std::endl;
		}
		else
		{
			std::cout << SDL_NumJoysticks() << " joysticks connected" << std::endl;
			joy_stick = SDL_JoystickOpen(0);
			std::cout << "JoystickID: " << SDL_JoystickInstanceID(joy_stick) << std::endl;
		}
	}

	bool Input::is_key(int key) const
	{
		std::vector<int>::const_iterator itr;
		for (itr = this->m_keys.begin(); itr != this->m_keys.end(); ++itr)
		{
			if (key == *itr)
			{
				return true;
			}
		}

		return false;
	}

	bool Input::is_key_pressed(int key) const
	{
		std::vector<int>::iterator itr;
		for (itr = this->m_pressed_keys.begin(); itr != this->m_pressed_keys.end(); ++itr)
		{
			if (key == *itr)
			{
				this->m_pressed_keys.erase(itr);
				return true;
			}
		}

		return false;
	}

	bool Input::is_key_released(int key) const
	{
		std::vector<int>::iterator itr;
		for (itr = this->m_released_keys.begin(); itr != this->m_released_keys.end(); ++itr)
		{
			if (key == *itr)
			{
				this->m_released_keys.erase(itr);
				return true;
			}
		}

		return false;
	}

	bool Input::is_mouse_button(int button) const
	{
		std::vector<int>::const_iterator itr;
		for (itr = this->m_m_buttons.begin(); itr != this->m_m_buttons.end(); ++itr)
		{
			if (button == *itr)
			{
				return true;
			}
		}

		return false;
	}

	bool Input::is_mouse_button_pressed(int button) const
	{
		std::vector<int>::iterator itr;
		for (itr = this->m_pressed_mouse_buttons.begin(); itr != this->m_pressed_mouse_buttons.end(); ++itr)
		{
			if (button == *itr)
			{
				this->m_pressed_mouse_buttons.erase(itr);
				return true;
			}
		}

		return false;
	}

	bool Input::is_mouse_button_released(int button) const
	{
		std::vector<int>::iterator itr;
		for (itr = this->m_released_mouse_buttons.begin(); itr != this->m_released_mouse_buttons.end(); ++itr)
		{
			if (button == *itr)
			{
				this->m_released_mouse_buttons.erase(itr);
				return true;
			}
		}

		return false;
	}

	bool Input::is_controller_button(int button) const
	{
		std::vector<int>::const_iterator itr;
		for (itr = this->m_controller_buttons.begin(); itr != this->m_controller_buttons.end(); ++itr)
		{
			if (button == *itr)
			{
				return true;
			}
		}

		return false;
	}

	bool Input::is_controller_button_pressed(int button) const
	{
		std::vector<int>::iterator itr;
		for (itr = this->m_pressed_controller_buttons.begin(); itr != this->m_pressed_controller_buttons.end(); ++itr)
		{
			if (button == *itr)
			{
				this->m_pressed_controller_buttons.erase(itr);
				return true;
			}
		}

		return false;
	}

	bool Input::is_controller_button_released(int button) const
	{
		std::vector<int>::iterator itr;
		for (itr = this->m_released_controller_buttons.begin(); itr != this->m_released_controller_buttons.end(); ++itr)
		{
			if (button == *itr)
			{
				this->m_released_controller_buttons.erase(itr);
				return true;
			}
		}

		return false;
	}

	int Input::wheel() const
	{
		return this->m_wheel;
	}

	bool Input::mouse_in_motion() const
	{
		return this->m_mouse_motion;
	}

	glm::ivec2 Input::joy_stick_direction() const
	{
		return this->m_joy_stick_direction;
	}

	int Input::joy_stick_direction_x() const
	{
		return this->m_joy_stick_direction.x;
	}

	int Input::joy_stick_direction_y() const
	{
		return this->m_joy_stick_direction.y;
	}

	glm::ivec2 Input::cursor() const
	{
		return this->m_cursor;
	}

	int Input::cursor_x() const
	{
		return this->m_cursor.x;
	}

	int Input::cursor_y() const
	{
		return this->m_cursor.y;
	}

	void Input::dead_zone(int dead_zone)
	{
		this->m_dead_zone = dead_zone;
	}

	int Input::dead_zone() const
	{
		return this->m_dead_zone;
	}

	void Input::invert_x(bool invert)
	{
		this->m_invert_x = invert;
	}

	bool Input::invert_x() const
	{
		return this->m_invert_x;
	}

	void Input::invert_y(bool invert)
	{
		this->m_invert_y = invert;
	}

	bool Input::invert_y() const
	{
		return this->m_invert_y;
	}
}