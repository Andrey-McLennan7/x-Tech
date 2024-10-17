#include "Core.h"
#include "Entity.h"
#include "Debug.h"
#include "Window.h"

#include <iostream>
#include <exception>

namespace xTech
{
	std::shared_ptr<Core> Core::initialize()
	{
		std::shared_ptr<Core> rtn = std::make_shared<Core>();

		// Create window
		rtn->m_window = std::make_shared<Window>();

		// Make pointer reference to self
		rtn->m_self = rtn;

		rtn->m_running = true;

		return rtn;
	}

	void Core::run()
	{
		// Start game loop
		while (this->m_running)
		{
			// Input
			SDL_Event e;
			while (SDL_PollEvent(&e))
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					this->m_running = false;
					break;
				}
			}

			// Update
			std::vector<std::shared_ptr<Entity>>::iterator itr;
			for (itr = this->m_entities.begin(); itr < this->m_entities.end(); ++itr)
			{
				(*itr)->tick();
			}

			// Render
			for (itr = this->m_entities.begin(); itr < this->m_entities.end(); ++itr)
			{
				(*itr)->display();
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