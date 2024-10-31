#include <SDL2/SDL.h>
#include <memory>

namespace xTech
{
	class Core;
	class Entity;

	class Window
	{
	// Private data members
	private:

		SDL_Window* m_id;

		std::weak_ptr<Core> m_core;

		int m_width;
		int m_height;

		float m_delta_time;
		unsigned int m_tick_count;

	// Public member functions
	public:

		Window(int width = 1920, int height = 1080);
		~Window();

		void delta_time();

		void input();
		void tick();
		void display();

		SDL_Window* ID();

		int get_width();
		int get_height();

		void set_width(int width);
		void set_height(int height);

		friend Core;
	};
}