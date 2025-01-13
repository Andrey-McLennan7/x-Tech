#include "InputDevice.h"

namespace xTech
{
	bool InputDevice::is(int input)
	{
		std::vector<int>::const_iterator itr;
		for (itr = this->m_is.begin(); itr != this->m_is.end(); ++itr)
		{
			if (input == *itr)
			{
				return true;
			}
		}

		return false;
	}

	bool InputDevice::is_pressed(int input)
	{
		std::vector<int>::iterator itr;
		for (itr = this->m_is_pressed.begin(); itr != this->m_is_pressed.end(); ++itr)
		{
			if (input == *itr)
			{
				this->m_is_pressed.erase(itr);
				return true;
			}
		}

		return false;
	}

	bool InputDevice::is_released(int input)
	{
		std::vector<int>::iterator itr;
		for (itr = this->m_is_released.begin(); itr != this->m_is_released.end(); ++itr)
		{
			if (input == *itr)
			{
				this->m_is_released.erase(itr);
				return true;
			}
		}

		return false;
	}
}