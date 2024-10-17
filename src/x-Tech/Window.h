#include <SDL.h>

namespace xTech
{
	class Window
	{
	private:

		SDL_Window* m_id;

		int m_width;
		int m_height;

	public:

		Window(int width = 1920, int height = 1080);
		~Window();

		int get_width();
		int get_height();
	};
}