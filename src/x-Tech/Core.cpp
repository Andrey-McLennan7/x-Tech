#include "Core.h"
#include "Entity.h"
#include "Debug.h"

#include <iostream>
#include <exception>

namespace xTech
{
	std::shared_ptr<Core> Core::initialize()
	{
		std::shared_ptr<Core> rtn = std::make_shared<Core>();

		// Initialise everything in the SDL2 library
		if (SDL_Init(SDL_INIT_EVERYTHING))
		{
			SDL_Log("ERROR::FAILED TO INITIALISE SDL2::%s", SDL_GetError());
			throw std::exception();
		}

		// Create SDL2 window
		rtn->m_window = SDL_CreateWindow("x-Tech", 1920, 1080, SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

		if (!rtn->m_window)
		{
			SDL_Log("ERROR::FAILED TO CREATE SDL2 WINDOW::%s", SDL_GetError());
			throw std::exception();
		}

		// Make pointer reference to self
		rtn->m_self = rtn;

		rtn->m_running = false;

		return rtn;
	}

	Core::~Core()
	{
		SDL_DestroyWindow(this->m_window);
		SDL_Quit();
	}

	void Core::run()
	{
		// Debug
		Debug::print("Hello World");

		// Start game loop
		while (this->m_running)
		{
			// Update
			for (size_t ci{ 0 }; ci < this->m_entities.size(); ++ci)
			{
				this->m_entities.at(ci)->tick();
			}

			// Render
			for (size_t ci{ 0 }; ci < this->m_entities.size(); ++ci)
			{
				this->m_entities.at(ci)->display();
			}
		}
	}

	void Core::end()
	{
		this->m_running = false;
	}

	std::shared_ptr<Entity> Core::add_entity()
	{
		std::shared_ptr<Entity> rtn = std::make_shared<Entity>();

		rtn->m_core = this->m_self;
		rtn->m_self = rtn;

		this->m_entities.push_back(rtn);

		return rtn;
	}
}