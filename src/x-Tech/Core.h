#include <memory>
#include <vector>

namespace xTech
{
	class Entity;
	class Window;

	// Core implementation
	class Core
	{
	// Private data members
	private:

		std::shared_ptr<Window> m_window;
		bool m_running;

		std::vector<std::shared_ptr<Entity>> m_entities;
		std::weak_ptr<Core> m_self;

		float m_delta_time;
		unsigned int m_tick_count;

	// Private member functions
	private:

		void delta_time();

	// Public member functions
	public:

		static std::shared_ptr<Core> initialize();

		void run();
		void end();

		std::shared_ptr<Entity> add_entity();
		std::shared_ptr<Window> get_window();

		float get_delta_time();

		friend Entity;
	};
}