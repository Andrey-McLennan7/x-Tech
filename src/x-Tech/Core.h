#include "SDL.h"

#include <memory>
#include <vector>

namespace xTech
{
	// Forward decleration
	class Entity;

	// Core implementation
	class Core
	{
	public:

		static std::shared_ptr<Core> initialize();

	private:

		SDL_Window* m_window;
		bool m_running;

		std::vector<std::shared_ptr<Entity>> m_entities;
		std::weak_ptr<Core> m_self;

	public:

		~Core();

		void run();
		void end();

		std::shared_ptr<Entity> add_entity();
	};
}