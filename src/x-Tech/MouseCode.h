#pragma once

#ifndef X_TECH_MOUSECODE_H
#define X_TECH_MOUSECODE_H

namespace xTech
{
	enum MouseButton
	{
		MOUSE_SCROLL_UP = 1,
		MOUSE_SCROLL_DOWN = -1,

		MOUSE_LEFT = SDL_BUTTON_LEFT,
		MOUSE_RIGHT = SDL_BUTTON_RIGHT,
		MOUSE_MIDDLE = SDL_BUTTON_MIDDLE
	};
}

#endif