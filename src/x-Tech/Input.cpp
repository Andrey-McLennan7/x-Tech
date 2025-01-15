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

		std::cout << "Controller status: ";
		if (SDL_NumJoysticks() < 1)
		{
			std::cout << "No controllers connected" << std::endl;
		}
		else
		{
			std::cout << SDL_NumJoysticks() << " controllers connected" << std::endl;

			for (int i{ 0 }; i < SDL_NumJoysticks(); ++i)
			{
				this->m_controllers.push_back(std::make_shared<Controller>());
				this->m_controllers[i]->m_id = SDL_JoystickOpen(i);

				std::cout << "Controller " << i << " ID: " << SDL_JoystickInstanceID(this->m_controllers[i]->m_id) << std::endl;
			}
		}
	}

	Input::~Input()
	{
		std::vector<std::shared_ptr<Controller>>::iterator itr;
		for (itr = this->m_controllers.begin(); itr != this->m_controllers.end(); ++itr)
		{
			SDL_JoystickClose((*itr)->m_id);
		}

		this->m_controllers.clear();
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
		if (this->m_controllers.empty())
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

	int Input::controller_number() const
	{
		return this->m_controllers.size();
	}
}