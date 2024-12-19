#include "Input.h"

namespace xTech
{
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

	bool Input::is_button(int button) const
	{
		std::vector<int>::const_iterator itr;
		for (itr = this->m_buttons.begin(); itr != this->m_buttons.end(); ++itr)
		{
			if (button == *itr)
			{
				return true;
			}
		}

		return false;
	}

	bool Input::is_button_pressed(int button) const
	{
		std::vector<int>::iterator itr;
		for (itr = this->m_pressed_buttons.begin(); itr != this->m_pressed_buttons.end(); ++itr)
		{
			if (button == *itr)
			{
				this->m_pressed_buttons.erase(itr);
				return true;
			}
		}

		return false;
	}

	bool Input::is_button_released(int button) const
	{
		std::vector<int>::iterator itr;
		for (itr = this->m_released_buttons.begin(); itr != this->m_released_buttons.end(); ++itr)
		{
			if (button == *itr)
			{
				this->m_released_buttons.erase(itr);
				return true;
			}
		}

		return false;
	}

	int Input::wheel() const
	{
		return this->m_wheel;
	}

	bool Input::in_motion() const
	{
		return this->m_motion;
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
}