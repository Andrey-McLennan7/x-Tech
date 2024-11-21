#include <memory>
#include <vector>

namespace xTech
{
	class Entity;
	class Window;
	class Cache;
	class Audio;

	// Core implementation
	class Core
	{
	// Private data members
	private:

		std::shared_ptr<Window> m_window;
		//std::shared_ptr<Input> m_input;
		std::shared_ptr<Audio> m_audio;
		std::shared_ptr<Cache> m_cache;
		//std::shared_ptr<Physics> m_physics;

		bool m_run;

		std::vector<std::shared_ptr<Entity>> m_entities;
		std::weak_ptr<Core> m_self;

	// Public member functions
	public:

		static std::shared_ptr<Core> initialize();

		void run();
		void end();

		std::shared_ptr<Entity> add_entity();

		std::shared_ptr<Window> window() const;
		std::shared_ptr<Cache> cache() const;

		friend Entity;
	};
}