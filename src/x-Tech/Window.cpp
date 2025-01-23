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
		m_delta_time{ 0.0f },
		m_tick_count{ 0 }
	{
		// Create SDL2 window
		this->m_id = SDL_CreateWindow("x-Tech", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width,
			height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

		if (!this->m_id)
		{
			SDL_Log("ERROR::%s", SDL_GetError());
			throw std::runtime_error("FAILED TO CREATE SDL2 WINDOW");
		}

		// Create OpenGL context
		this->m_context = SDL_GL_CreateContext(this->m_id);

		// Initialise and check for GLEW
		if (glewInit() != GLEW_OK)
		{
			throw std::runtime_error("ERROR::FAILED TO INITIALISE GLEW");
		}

		// Enable/Disable VSYNC
		SDL_GL_SetSwapInterval(0);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	Window::~Window()
	{
		SDL_GL_DeleteContext(this->m_context);
		SDL_DestroyWindow(this->m_id);
		SDL_Quit();
	}

	void Window::tick()
	{
		// Wait until 16ms has elapsed since last frame
		while (!SDL_TICKS_PASSED(SDL_GetTicks64(), this->m_tick_count + 16));

		// Delta time is the difference in ticks from last frame
		Uint64 ticks{ SDL_GetTicks64() };

		this->m_delta_time = (ticks - this->m_tick_count) / 1000.0f;
		this->m_tick_count = ticks;

		// Clamp maximum delta time value
		if (this->m_delta_time > 0.05f)
		{
			this->m_delta_time = 0.05f;
		}

		int w{ 0 };
		int h{ 0 };

		SDL_GetWindowSize(this->m_id, &w, &h);
		glViewport(0, 0, w, h);
	}

	void Window::size(const glm::ivec2& size)
	{
		SDL_SetWindowSize(this->m_id, size.x, size.y);
	}

	void Window::size(int width, int height)
	{
		this->size(glm::ivec2{ width, height });
	}

	glm::ivec2 Window::size() const
	{
		int w{ 0 };
		int h{ 0 };

		SDL_GetWindowSize(this->m_id, &w, &h);

		glm::ivec2 rtn{ w, h };

		return rtn;
	}

	int Window::size_x() const
	{
		return this->size().x;
	}

	int Window::size_y() const
	{
		return this->size().y;
	}

	float Window::delta_time()
	{
		return this->m_delta_time;
	}

	void Window::resizable(bool resizable)
	{
		if (resizable)
		{
			SDL_SetWindowResizable(this->m_id, SDL_TRUE);
		}
		else
		{
			SDL_SetWindowResizable(this->m_id, SDL_FALSE);
		}
	}

	SDL_Window* Window::ID()
	{
		return this->m_id;
	}
}