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
		Uint64 m_tick_count;

	// Public member functions
	public:

		Window(int width = 1240, int height = 720);
		~Window();

		void tick();

		void size(const glm::ivec2& size);
		void size(int width, int height);

		glm::ivec2 size() const;

		int size_x() const;
		int size_y() const;

		float delta_time();

		void resizable(bool resizable = true);

		SDL_Window* ID();

		friend Core;
	};
}

#endif