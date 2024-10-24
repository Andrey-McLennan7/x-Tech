#include "Core.h"
#include "Entity.h"
#include "Debug.h"
#include "Window.h"
#include "Transform.h"

#include <GL/glew.h>
#include <SDL.h>

namespace xTech
{
	void Core::delta_time()
	{
		// Wait until 16ms has elapsed since last frame
		while (!SDL_TICKS_PASSED(SDL_GetTicks64(), this->m_tick_count + 16));

		// Delta time is the difference in ticks from last frame
		this->m_delta_time = (SDL_GetTicks64() - this->m_tick_count) / 1000.0f;
		this->m_tick_count = SDL_GetTicks64();

		// Clamp maximum delta time value
		if (this->m_delta_time > 0.05f)
		{
			this->m_delta_time = 0.05f;
		}
	}

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
			// Calculate delta time
			this->delta_time();

			/* Input */
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

			/* Update */
			int width{ 0 }, height{ 0 };
			SDL_GetWindowSize(this->m_window->ID(), &width, &height);
			glViewport(0, 0, width, height);

			this->m_window->set_width(width);
			this->m_window->set_height(height);

			std::vector<std::shared_ptr<Entity>>::iterator itr;
			for (itr = this->m_entities.begin(); itr < this->m_entities.end(); ++itr)
			{
				(*itr)->tick();
			}

			/* Render */
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0.1f, 0.2f, 0.5f, 1.0f);

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
		this->m_running = false;
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

	std::shared_ptr<Window> Core::get_window()
	{
		return this->m_window;
	}

	float Core::get_delta_time()
	{
		return this->m_delta_time;
	}
}