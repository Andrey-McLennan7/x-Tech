#include "Window.h"
#include <exception>

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
			SDL_Log("ERROR::FAILED TO INITIALISE SDL2::%s", SDL_GetError());
			throw std::exception();
		}

		// Create SDL2 window
		this->m_id = SDL_CreateWindow("x-Tech", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->m_width,
			this->m_height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

		if (!this->m_id)
		{
			SDL_Log("ERROR::FAILED TO CREATE SDL2 WINDOW::%s", SDL_GetError());
			throw std::exception();
		}
	}

	Window::~Window()
	{
		SDL_DestroyWindow(this->m_id);
		SDL_Quit();
	}

	int Window::get_width()
	{
		return this->m_width;
	}

	int Window::get_height()
	{
		return this->m_height;
	}
}