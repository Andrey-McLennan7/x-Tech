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
		bool m_run;

		std::vector<std::shared_ptr<Entity>> m_entities;
		std::vector<std::shared_ptr<Entity>>::iterator m_ent_itr;
		std::weak_ptr<Core> m_self;

	// Public member functions
	public:

		static std::shared_ptr<Core> initialize();

		void run();
		void end();

		std::shared_ptr<Entity> add_entity();
		std::shared_ptr<Window> get_window();

		friend Entity;
		friend Window;
	};
}