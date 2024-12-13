#pragma once

#ifndef X_TECH_MOUSE_H
#define X_TECH_MOUSE_H

#include <vector>

namespace xTech
{
	class Core;

	struct Cursor
	{
		int m_x;
		int m_y;
	};

	class Mouse
	{
	private:

		Cursor m_state;

		mutable std::vector<int> m_buttons;

	public:

		bool is_mouse_down(int mouse) const;
		bool is_mouse_up(int mouse) const;

		void mouse_x(int x);
		int mouse_x() const;

		void mouse_y(int y);
		int mouse_y() const;

		void state(int x, int y);
		void state(int* x, int* y) const;

		friend class Core;
	};
}

#endif