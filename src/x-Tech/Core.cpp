#include "Core.h"
#include "Entity.h"
#include "Transform.h"

#include "Window.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>

namespace xTech
{
	std::shared_ptr<Core> Core::initialize()
	{
		std::shared_ptr<Core> rtn = std::make_shared<Core>();

		// Make pointer reference to self
		rtn->m_self = rtn;

		rtn->m_run = true;

		// Create window
		rtn->m_window = std::make_shared<Window>();

		return rtn;
	}

	void Core::run()
	{
		// Start game loop
		while (this->m_run)
		{
			// Input
			// Read mouse input
			SDL_Event e;

			// Read keyboard input
			const Uint8* state{ SDL_GetKeyboardState(NULL) };

			while (SDL_PollEvent(&e))
			{
				if (e.type == SDL_QUIT || state[SDL_SCANCODE_ESCAPE])
				{
					this->end();
				}
			}

			// Update
			this->m_window->tick();

			std::vector<std::shared_ptr<Entity>>::iterator itr;
			for (itr = this->m_entities.begin(); itr < this->m_entities.end(); ++itr)
			{
				(*itr)->tick();
			}

			// Render
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0.1f, 0.1f, 0.3f, 1.0f);

			glEnable(GL_DEPTH_TEST);

			for (itr = this->m_entities.begin(); itr < this->m_entities.end(); ++itr)
			{
				(*itr)->display();
			}

			SDL_GL_SwapWindow(this->m_window->ID());
		}
	}

	void Core::end()
	{
		this->m_run = false;
	}

	std::shared_ptr<Entity> Core::add_entity()
	{
		std::shared_ptr<Entity> rtn = std::make_shared<Entity>();

		rtn->m_core = this->m_self;
		rtn->m_self = rtn;

		rtn->add_component<Transform>();

		this->m_entities.push_back(rtn);

		return rtn;
	}

	std::shared_ptr<Window> Core::window() const
	{
		return this->m_window;
	}
}