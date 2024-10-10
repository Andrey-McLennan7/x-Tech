#include <memory>
#include <vector>

namespace xTech
{
	class Entity;

	class Core
	{
	private:

		//SDL_Window* m_window;
		bool m_running;

		std::vector<std::shared_ptr<Entity>> m_entities;
		std::weak_ptr<Core> m_self;

	public:

		static std::shared_ptr<Core> initialize();

		void run();
		void end();

		std::shared_ptr<Entity> add_entity();
	};
}