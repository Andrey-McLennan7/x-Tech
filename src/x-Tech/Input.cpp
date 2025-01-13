#include "Input.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Controller.h"

#include <iostream>

namespace xTech
{
	Input::Input() 
	{
		this->m_keyboard = std::make_shared<Keyboard>();
		this->m_mouse = std::make_shared<Mouse>();

		if (SDL_NumJoysticks() < 1)
		{
			std::cout << "No joystick available" << std::endl;
		}
		else
		{
			std::cout << SDL_NumJoysticks() << " joysticks connected" << std::endl;

			for (int i{ 0 }; i < SDL_NumJoysticks(); ++i)
			{
				this->m_controllers.push_back(std::make_shared<Controller>());
				this->m_controllers[i]->m_id = SDL_JoystickOpen(i);

				std::cout << "JoystickID: " << SDL_JoystickInstanceID(this->m_controllers[i]->m_id) << std::endl;
			}
		}
	}

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

	int Input::connected_controllers() const
	{
		return this->m_controllers.size();
	}
}