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
}