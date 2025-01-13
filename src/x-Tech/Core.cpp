#include "Core.h"
#include "Entity.h"
#include "Transform.h"

#include "Window.h"
#include "Camera.h"
#include "Cache.h"
#include "Input.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Controller.h"
#include "PointLight.h"

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

	std::shared_ptr<Camera> Core::current_camera() const
	{
		return this->m_current_camera.lock();
	}

	std::shared_ptr<PointLight> Core::current_light() const
	{
		return this->m_current_light.lock();
	}

	void Core::do_input()
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			// Quit program
			if (SDL_QUIT == e.type)
			{
				this->end();
			}

			// Read keyboard inputs
			if (SDL_KEYDOWN == e.type)
			{
				this->m_input->m_keyboard->m_is.push_back(e.key.keysym.sym);
				this->m_input->m_keyboard->m_is_pressed.push_back(e.key.keysym.sym);
			}
			else if (SDL_KEYUP == e.type)
			{
				std::vector<int>::iterator itr;
				for (itr = this->m_input->m_keyboard->m_is.begin(); itr != this->m_input->m_keyboard->m_is.end();)
				{
					if (e.key.keysym.sym == *itr)
					{
						itr = this->m_input->m_keyboard->m_is.erase(itr);
					}
					else
					{
						++itr;
					}
				}

				this->m_input->m_keyboard->m_is_released.push_back(e.key.keysym.sym);
			}

			// Read mouse inputs
			// Read motion
			if (SDL_MOUSEMOTION == e.type)
			{
				this->m_input->m_mouse->m_in_motion = true;
				this->m_input->m_mouse->m_cursor.x = e.motion.x;
				this->m_input->m_mouse->m_cursor.y = e.motion.y;
			}

			// Read button input
			if (SDL_MOUSEBUTTONDOWN == e.type)
			{
				this->m_input->m_mouse->m_is.push_back(e.button.button);
				this->m_input->m_mouse->m_is_pressed.push_back(e.button.button);
			}
			else if (SDL_MOUSEBUTTONUP == e.type)
			{
				std::vector<int>::iterator itr;
				for (itr = this->m_input->m_mouse->m_is.begin(); itr != this->m_input->m_mouse->m_is.end();)
				{
					if (e.button.button == *itr)
					{
						itr = this->m_input->m_mouse->m_is.erase(itr);
					}
					else
					{
						++itr;
					}
				}

				this->m_input->m_mouse->m_is_released.push_back(e.button.button);
			}
			else if (SDL_MOUSEWHEEL == e.type)
			{
				if (e.wheel.y > 0)
				{
					this->m_input->m_mouse->m_wheel = 1;
				}
				else if (e.wheel.y < 0)
				{
					this->m_input->m_mouse->m_wheel = -1;
				}
			}

			// Read controller inputs
			std::vector<std::shared_ptr<Controller>>::iterator controller;
			for (controller = this->m_input->m_controllers.begin(); controller != this->m_input->m_controllers.end(); ++controller)
			{
				// Read analog joy-stick motion
				if (SDL_JOYAXISMOTION == e.type)
				{
					if (0 == e.jaxis.which)
					{
						if (0 == e.jaxis.axis)
						{
							int x{ 0 };

							if (e.jaxis.value > (*controller)->m_dead_zone)
							{
								if ((*controller)->m_invert_x)
								{
									x = -1;
								}
								else
								{
									x = 1;
								}
							}
							else if (e.jaxis.value < -(*controller)->m_dead_zone)
							{
								if ((*controller)->m_invert_x)
								{
									x = 1;
								}
								else
								{
									x = -1;
								}
							}
							else
							{
								x = 0;
							}

							(*controller)->m_joy_stick_direction.x = x;
						}
						else if (1 == e.jaxis.axis)
						{
							int y{ 0 };

							if (e.jaxis.value > (*controller)->m_dead_zone)
							{
								if ((*controller)->m_invert_y)
								{
									y = -1;
								}
								else
								{
									y = 1;
								}
							}
							else if (e.jaxis.value < -(*controller)->m_dead_zone)
							{
								if ((*controller)->m_invert_y)
								{
									y = 1;
								}
								else
								{
									y = -1;
								}
							}
							else
							{
								y = 0;
							}

							(*controller)->m_joy_stick_direction.y = y;
						}
					}
				}

				// Read button inputs
				if (SDL_JOYBUTTONDOWN == e.type)
				{
					(*controller)->m_is.push_back(e.jbutton.button);
					(*controller)->m_is_pressed.push_back(e.jbutton.button);
				}
				else if (SDL_JOYBUTTONUP == e.type)
				{
					std::vector<int>::iterator itr;
					for (itr = (*controller)->m_is.begin(); itr != (*controller)->m_is.end();)
					{
						if (e.jbutton.button == *itr)
						{
							itr = (*controller)->m_is.erase(itr);
						}
						else
						{
							++itr;
						}
					}

					(*controller)->m_is_released.push_back(e.jbutton.button);
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
		// Keyboard
		this->m_input->m_keyboard->m_is_pressed.clear();
		this->m_input->m_keyboard->m_is_released.clear();

		// Mouse
		this->m_input->m_mouse->m_is_pressed.clear();
		this->m_input->m_mouse->m_is_released.clear();
		this->m_input->m_mouse->m_wheel = 0;
		this->m_input->m_mouse->m_in_motion = false;

		// Controller
		std::vector<std::shared_ptr<Controller>>::iterator controller;
		for (controller = this->m_input->m_controllers.begin(); controller != this->m_input->m_controllers.end(); ++controller)
		{
			(*controller)->m_is_pressed.clear();
			(*controller)->m_is_released.clear();
		}
	}

	void Core::do_render()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(this->m_background_colour.x, this->m_background_colour.y, this->m_background_colour.z, 1.0f);

		glEnable(GL_DEPTH_TEST);

		std::vector<std::weak_ptr<Camera>>::iterator c_itr;
		for (c_itr = this->m_cameras.begin(); c_itr != this->m_cameras.end(); ++c_itr)
		{
			this->m_current_camera = *c_itr;

			std::vector<std::weak_ptr<PointLight>>::iterator l_itr;
			for (l_itr = this->m_lights.begin(); l_itr != this->m_lights.end(); ++l_itr)
			{
				this->m_current_light = *l_itr;
			}

			std::vector<std::shared_ptr<Entity>>::iterator e_itr;
			for (e_itr = this->m_entities.begin(); e_itr < this->m_entities.end(); ++e_itr)
			{
				(*e_itr)->display();
			}
		}

		std::vector<std::shared_ptr<Entity>>::iterator g_itr;
		for (g_itr = this->m_entities.begin(); g_itr < this->m_entities.end(); ++g_itr)
		{
			(*g_itr)->gui();
		}

		SDL_GL_SwapWindow(this->m_window->ID());
	}

	std::shared_ptr<Core> Core::initialize()
	{
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
		{
			throw std::runtime_error("ERROR::FAILED TO INITIALIZE SDL2");
		}

		std::shared_ptr<Core> rtn = std::make_shared<Core>();

		// Make pointer reference to self
		rtn->m_self = rtn;
		rtn->m_run = true;

		// Create core components
		rtn->m_window = std::make_shared<Window>();
		rtn->m_cache = std::make_shared<Cache>();
		rtn->m_input = std::make_shared<Input>();

		// Create the main camera
		std::shared_ptr<Entity> camera{ rtn->add_entity() };
		camera->add_component<Camera>();

		rtn->m_background_colour = glm::vec3{ 0.1f, 0.1f, 0.3f };

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

	std::shared_ptr<Entity> Core::add_entity()
	{
		std::shared_ptr<Entity> rtn{ std::make_shared<Entity>() };

		rtn->m_core = this->m_self;
		rtn->m_self = rtn;

		rtn->m_transform = rtn->add_component<Transform>();

		if (this->m_entities.empty())
		{
			rtn->m_name = "Entity";
		}
		else
		{
			rtn->m_name = "Entity" + std::to_string(this->m_entities.size());
		}

		this->m_entities.push_back(rtn);

		return rtn;
	}

	std::shared_ptr<Entity> Core::get_entity_by_name(const std::string& name) const
	{
		std::vector<std::shared_ptr<Entity>>::const_iterator itr;
		for (itr = this->m_entities.begin(); itr != this->m_entities.end(); ++itr)
		{
			if (name == (*itr)->m_name)
			{
				return *itr;
			}
		}

		throw std::runtime_error("ERROR::ENTITY NOT FOUND");
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

	std::shared_ptr<Camera> Core::camera(int index) const
	{
		if (this->m_cameras.empty())
		{
			throw std::runtime_error("ERROR::NO CAMERAS ARE FOUND");
		}

		if (index < 0)
		{
			index = 0;
		}
		else if (index >= this->m_cameras.size())
		{
			index = this->m_cameras.size() - 1;
		}

		return this->m_cameras[index].lock();
	}

	std::shared_ptr<PointLight> Core::light(int index) const
	{
		if (this->m_lights.empty())
		{
			throw std::runtime_error("ERROR::NO LIGHTS ARE IN THE SCENE");
		}

		if (index < 0)
		{
			index = 0;
		}
		else if (index >= this->m_lights.size())
		{
			index = this->m_lights.size() - 1;
		}

		return this->m_lights[index].lock();
	}

	void Core::background(const glm::vec3& colour)
	{
		this->m_background_colour = colour / 256.0f;
	}

	glm::vec3 Core::background() const
	{
		return this->m_background_colour;
	}
}