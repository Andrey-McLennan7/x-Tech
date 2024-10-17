#include "SDL.h"

#include <memory>
#include <vector>

namespace xTech
{
	class Entity;
	class Window;

	// Core implementation
	class Core
	{
	public:

		static std::shared_ptr<Core> initialize();

	private:

		std::shared_ptr<Window> m_window;
		bool m_running;

		std::vector<std::shared_ptr<Entity>> m_entities;
		std::weak_ptr<Core> m_self;

	public:

		void run();
		void end();

		std::shared_ptr<Entity> add_entity();
	};
}