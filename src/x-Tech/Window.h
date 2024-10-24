#include <SDL.h>

namespace xTech
{
	class Window
	{
	// Private data members
	private:

		SDL_Window* m_id;

		int m_width;
		int m_height;

	// Public member functions
	public:

		Window(int width = 1920, int height = 1080);
		~Window();

		SDL_Window* ID();

		int get_width();
		int get_height();

		void set_width(int width);
		void set_height(int height);
	};
}