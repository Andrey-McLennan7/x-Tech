#include "Mouse.h"

namespace xTech
{
	Mouse::Mouse() :
		m_in_motion{ false },
		m_cursor{ 0 },
		m_wheel{ 0 }
	{}

	int Mouse::wheel() const
	{
		return this->m_wheel;
	}

	bool Mouse::in_motion() const
	{
		return this->m_in_motion;
	}

	glm::ivec2 Mouse::cursor() const
	{
		return this->m_cursor;
	}

	int Mouse::cursor_x() const
	{
		return this->m_cursor.x;
	}

	int Mouse::cursor_y() const
	{
		return this->m_cursor.y;
	}
}