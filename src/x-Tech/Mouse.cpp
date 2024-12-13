#include "Mouse.h"

namespace xTech
{
	bool Mouse::is_mouse_down(int mouse) const
	{
		std::vector<int>::const_iterator itr;
		for (itr = this->m_buttons.begin(); itr != this->m_buttons.end(); ++itr)
		{
			if (mouse == *itr)
			{
				return true;
			}
		}

		return false;
	}

	bool Mouse::is_mouse_up(int mouse) const
	{
		return false;
	}

	void Mouse::mouse_x(int x)
	{
		this->m_state.m_x = x;
	}

	int Mouse::mouse_x() const
	{
		return this->m_state.m_x;
	}

	void Mouse::mouse_y(int y)
	{
		this->m_state.m_y = y;
	}

	int Mouse::mouse_y() const
	{
		return this->m_state.m_y;
	}

	void Mouse::state(int x, int y)
	{
		this->m_state.m_x = x;
		this->m_state.m_y = y;
	}

	void Mouse::state(int* x, int* y) const
	{
		*x = this->m_state.m_x;
		*y = this->m_state.m_y;
	}
}