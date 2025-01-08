#include "Core.h"
#include "Entity.h"
#include "Transform.h"

#include "Window.h"
#include "Camera.h"
#include "Cache.h"
#include "Input.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <AL/al.h>
#include <AL/alc.h>

#include <iostream>

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
		Core* core{ (Core*)_core };

		core->do_input();
		core->do_tick();
		core->do_render();
	}

	void Core::do_input()
	{
		/* Input */
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			// Quit program
			if (SDL_QUIT == e.type)
			{
				this->end();
			}

			// Detect keyboard inputs
			if (SDL_KEYDOWN == e.type)
			{
				this->m_input->m_keys.push_back(e.key.keysym.sym);
				this->m_input->m_pressed_keys.push_back(e.key.keysym.sym);
			}
			else if (SDL_KEYUP == e.type)
			{
				std::vector<int>::iterator itr;
				for (itr = this->m_input->m_keys.begin(); itr != this->m_input->m_keys.end();)
				{
					if (e.key.keysym.sym == *itr)
					{
						itr = this->m_input->m_keys.erase(itr);
					}
					else
					{
						++itr;
					}
				}

				this->m_input->m_released_keys.push_back(e.key.keysym.sym);
			}

			// Detect mouse inputs
			if (SDL_MOUSEMOTION == e.type)
			{
				this->m_input->m_motion = true;
				this->m_input->m_cursor.x = e.motion.x;
				this->m_input->m_cursor.y = e.motion.y;
			}

			if (SDL_MOUSEBUTTONDOWN == e.type)
			{
				this->m_input->m_buttons.push_back(e.button.button);
				this->m_input->m_pressed_buttons.push_back(e.button.button);
			}
			else if (SDL_MOUSEBUTTONUP == e.type)
			{
				std::vector<int>::iterator itr;
				for (itr = this->m_input->m_buttons.begin(); itr != this->m_input->m_buttons.end();)
				{
					if (e.button.button == *itr)
					{
						itr = this->m_input->m_buttons.erase(itr);
					}
					else
					{
						++itr;
					}
				}

				this->m_input->m_released_buttons.push_back(e.button.button);
			}
			else if (SDL_MOUSEWHEEL == e.type)
			{
				if (e.wheel.y > 0)
				{
					this->m_input->m_wheel = 1;
				}
				else if (e.wheel.y < 0)
				{
					this->m_input->m_wheel = -1;
				}
			}
		}
	}

	void Core::do_tick()
	{
		this->m_window->tick();

		// Execute on specified ticks randomly
		std::vector<std::shared_ptr<Entity>>::iterator itr;
		for (itr = this->m_entities.begin(); itr != this->m_entities.end(); ++itr)
		{
			(*itr)->fixed_tick();
		}

		// Execute on every tick sequentially
		for (itr = this->m_entities.begin(); itr != this->m_entities.end(); ++itr)
		{
			(*itr)->tick();
		}

		// Be the last tick to execute sequentially
		for (itr = this->m_entities.begin(); itr != this->m_entities.end(); ++itr)
		{
			(*itr)->late_tick();
		}

		// Clear input buffers
		this->m_input->m_pressed_keys.clear();
		this->m_input->m_released_keys.clear();
		this->m_input->m_pressed_buttons.clear();
		this->m_input->m_released_buttons.clear();
		this->m_input->m_wheel = 0;
		this->m_input->m_motion = false;
	}

	void Core::do_render()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.1f, 0.1f, 0.3f, 1.0f);

		glEnable(GL_DEPTH_TEST);

		std::vector<std::shared_ptr<Entity>>::iterator itr;
		for (itr = this->m_entities.begin(); itr < this->m_entities.end(); ++itr)
		{
			(*itr)->display();
		}

		for (itr = this->m_entities.begin(); itr < this->m_entities.end(); ++itr)
		{
			(*itr)->gui();
		}

		SDL_GL_SwapWindow(this->m_window->ID());
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

		// Create default camera entity
		std::shared_ptr<Entity> camera = rtn->add_entity();
		rtn->m_camera = camera->add_component<Camera>();

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

	std::shared_ptr<Camera> Core::camera() const
	{
		return this->m_camera;
	}
}