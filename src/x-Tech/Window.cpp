#include "Window.h"
#include <stdexcept>
#include <GL/glew.h>

namespace xTech
{
	Window::Window(int width, int height) :
		m_id{ nullptr },
		m_width { width },
		m_height{ height }
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