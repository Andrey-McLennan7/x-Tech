#include <memory>
#include <vector>

namespace xTech
{
	class Core;
	class Component;

	class Entity
	{
	private:

		std::vector<std::shared_ptr<Component>> m_components;

		std::weak_ptr<Core> m_core;
		std::weak_ptr<Entity> m_self;

		bool m_alive;

		void tick();
		void display();

	public:

		~Entity() {};

		template <typename T>
		std::shared_ptr<T> add_component()
		{
			std::shared_ptr<T> rtn{ std::make_shared<T>() };

			rtn->m_entity = this->m_self;

			rtn->initialize();
			this->m_components.push_back(rtn);

			return rtn;
		}

		void kill();

		friend Core;
	};
}