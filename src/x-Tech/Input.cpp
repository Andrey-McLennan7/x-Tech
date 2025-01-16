#include "Input.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Controller.h"

#include "SDL2/SDL_events.h"

#include <iostream>

namespace xTech
{
	Input::Input() :
		m_keyboard{ std::make_shared<Keyboard>() },
		m_mouse{ std::make_shared<Mouse>() }
	{}

	std::shared_ptr<Keyboard> Input::keyboard()
	{
		return this->m_keyboard;
	}

	std::shared_ptr<Mouse> Input::mouse()
	{
		return this->m_mouse;
	}

	std::shared_ptr<Controller> Input::controller(int index)
	{
		if (!this->controllers_connected())
		{
			throw std::runtime_error("ERROR::NO CONTROLLER IS CONNECTED");
		}

		if (index < 0)
		{
			index = 0;
		}
		else if (index >= this->m_controllers.size())
		{
			index = this->m_controllers.size() - 1;
		}

		return this->m_controllers[index];
	}

	bool Input::controllers_connected() const
	{
		return !this->m_controllers.empty();
	}

	int Input::controllers_number() const
	{
		return this->m_controllers.size();
	}
}