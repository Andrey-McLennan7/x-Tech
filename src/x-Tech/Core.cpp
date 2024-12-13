#include "Core.h"
#include "Entity.h"
#include "Transform.h"

#include "Window.h"
#include "Cache.h"
#include "Input.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <AL/al.h>
#include <AL/alc.h>

#ifdef __EMSCRIPTEN__
	#include <emscripten.h>
#endif

#ifdef _WIN32
	#include <windows.h>
#else
	#include <unistd.h>
#endif

namespace xTech
{
	void Core::loop(void* _core)
	{
		Core* core{ (Core*) _core };

		/* Input */
		// Read mouse input
		SDL_Event e;

		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
			{
				core->end();
			}
			else if (e.type == SDL_KEYDOWN)
			{
				core->m_input->m_keys.push_back(e.key.keysym.sym);
				core->m_input->m_pressed_keys.push_back(e.key.keysym.sym);
			}
			else if (e.type == SDL_KEYUP)
			{
				std::vector<int>::iterator itr;
				for (itr = core->m_input->m_keys.begin(); itr != core->m_input->m_keys.end(); ++itr)
				{
					if ((*itr) == e.key.keysym.sym)
					{
						core->m_input->m_keys.erase(itr);
						--itr;
					}
				}

				core->m_input->m_released_keys.push_back(e.key.keysym.sym);
			}
		}

		/* Update */
		core->m_window->tick();

		// Execute on specified ticks randomly
		std::vector<std::shared_ptr<Entity>>::iterator itr;
		for (itr = core->m_entities.begin(); itr != core->m_entities.end(); ++itr)
		{
			(*itr)->fixed_tick();
		}

		// Execute on every tick sequentially
		for (itr = core->m_entities.begin(); itr != core->m_entities.end(); ++itr)
		{
			(*itr)->tick();
		}

		// Be the last tick to execute sequentially
		for (itr = core->m_entities.begin(); itr != core->m_entities.end(); ++itr)
		{
			(*itr)->late_tick();
		}

		// Clear input buffers
		core->m_input->m_pressed_keys.clear();
		core->m_input->m_released_keys.clear();

		/* Render */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.1f, 0.1f, 0.3f, 1.0f);

		glEnable(GL_DEPTH_TEST);

		for (itr = core->m_entities.begin(); itr < core->m_entities.end(); ++itr)
		{
			(*itr)->display();
		}

		for (itr = core->m_entities.begin(); itr < core->m_entities.end(); ++itr)
		{
			(*itr)->gui();
		}

		SDL_GL_SwapWindow(core->m_window->ID());
	}

	std::shared_ptr<Core> Core::initialize()
	{
		std::shared_ptr<Core> rtn = std::make_shared<Core>();

		// Make pointer reference to self
		rtn->m_self = rtn;
		rtn->m_run = true;

		// Create engine resrouces
		rtn->m_window = std::make_shared<Window>();
		rtn->m_cache = std::make_shared<Cache>();
		rtn->m_input = std::make_shared<Input>();

		ALCdevice* device{ alcOpenDevice(NULL) };

		if (!device)
		{
			throw std::runtime_error("ERROR::FAILED TO OPEN AUDIO DEVICE");
		}

		ALCcontext* context{ alcCreateContext(device, NULL) };

		if (!context)
		{
			alcCloseDevice(device);
			throw std::runtime_error("FAILED::FAILED TO CREATE AUDIO CONTEXT");
		}

		if (!alcMakeContextCurrent(context))
		{
			alcDestroyContext(context);
			alcCloseDevice(device);
			throw std::runtime_error("ERROR::FAILED TO MAKE CONTEXT CURRENT");
		}

		return rtn;
	}

	void Core::run()
	{
		#ifdef __EMSCRIPTEN__
			emscripten_set_main_loop_arg(loop, (void*)this, 0, 1);
		#else

		// Start game loop
		while (this->m_run)
		{
			loop(this);
		}

		#endif	
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

		rtn->m_transform = rtn->add_component<Transform>();

		this->m_entities.push_back(rtn);

		return rtn;
	}

	std::shared_ptr<Window> Core::window() const
	{
		return this->m_window;
	}

	std::shared_ptr<Cache> Core::cache() const
	{
		return this->m_cache;
	}

	std::shared_ptr<Input> Core::input() const
	{
		return this->m_input;
	}
}