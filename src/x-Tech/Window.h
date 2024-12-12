#pragma once

#ifndef X_TECH_WINDOW_H
#define X_TECH_WINDOW_H

#include <SDL2/SDL.h>
#include <memory>
#include <glm/glm.hpp>

namespace xTech
{
	class Core;
	class Entity;

	class Window
	{
		// Private data members
	private:

		SDL_Window* m_id;
		SDL_GLContext m_context;

		float m_delta_time;
		unsigned int m_tick_count;

		// Public member functions
	public:

		Window(int width = 1920, int height = 1080);
		~Window();

		void tick();

		glm::ivec2 size();
		float delta_time();

		SDL_Window* ID();

		friend Core;
	};
}

#endif