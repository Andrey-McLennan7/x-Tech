#include "Window.h"
#include "Core.h"
#include "Entity.h"

#include <vector>
#include <stdexcept>
#include <GL/glew.h>

namespace xTech
{
	Window::Window(int width, int height) :
		m_id{ nullptr },
		m_width { width },
		m_height{ height },
		m_delta_time{ 0.0f },
		m_tick_count{ 0 }
	{
		// Initialise everything in the SDL2 library
		if (SDL_Init(SDL_INIT_EVERYTHING))
		{
			SDL_Log("ERROR::%s", SDL_GetError());
			throw std::runtime_error("FAILED TO INITIALISE SDL2");
		}

		// Create SDL2 window
		this->m_id = SDL_CreateWindow("x-Tech", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->m_width,
			this->m_height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

		if (!this->m_id)
		{
			SDL_Log("ERROR::%s", SDL_GetError());
			throw std::runtime_error("FAILED TO CREATE SDL2 WINDOW");
		}

		SDL_GL_CreateContext(this->m_id);

		// Check GLEW
		if (glewInit() != GLEW_OK)
		{
			throw std::runtime_error("ERROR::FAILED TO INITIALISE GLEW");
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Window::delta_time()
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

	void Window::input()
	{
		// Read mouse input
		SDL_Event e;

		// Read keyboard input
		const Uint8* state{ SDL_GetKeyboardState(NULL) };

		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT || state[SDL_SCANCODE_ESCAPE])
			{
				this->m_core.lock()->end();
			}
		}
	}

	void Window::tick()
	{
		int width{ 0 }, height{ 0 };
		SDL_GetWindowSize(this->m_id, &width, &height);
		glViewport(0, 0, width, height);

		this->m_width = width;
		this->m_height = height;

		std::vector<std::shared_ptr<Entity>>::iterator itr;
		for (itr = this->m_core.lock()->m_entities.begin(); itr < this->m_core.lock()->m_entities.end(); ++itr)
		{
			(*itr)->tick();
		}
	}

	void Window::display()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.1f, 0.2f, 0.5f, 1.0f);

		glEnable(GL_DEPTH_TEST);

		std::vector<std::shared_ptr<Entity>>::iterator itr;
		for (itr = this->m_core.lock()->m_entities.begin(); itr < this->m_core.lock()->m_entities.end(); ++itr)
		{
			(*itr)->display();
		}

		SDL_GL_SwapWindow(this->m_id);
	}

	Window::~Window()
	{
		SDL_DestroyWindow(this->m_id);
		SDL_Quit();
	}

	SDL_Window* Window::ID()
	{
		return this->m_id;
	}

	int Window::get_width()
	{
		return this->m_width;
	}

	int Window::get_height()
	{
		return this->m_height;
	}

	void Window::set_width(int width)
	{
		this->m_width = width;
	}

	void Window::set_height(int height)
	{
		this->m_height = height;
	}
}