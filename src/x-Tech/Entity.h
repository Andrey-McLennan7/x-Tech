#include <memory>
#include <vector>
#include <stdexcept>

namespace xTech
{
	class Core;
	class Window;
	class Component;
	class Transform;

	class Entity
	{
	// Private data members
	private:

		std::vector<std::shared_ptr<Component>> m_components;

		std::weak_ptr<Core> m_core;
		std::weak_ptr<Entity> m_self;
		std::weak_ptr<Transform> m_transform;

		bool m_alive;

	// Private member functions
	private:

		void fixed_tick();
		void tick();
		void late_tick();

		void display();

	// Public member functions
	public:

		~Entity() {};

		template <typename T>
		std::shared_ptr<T> add_component()
		{
			std::shared_ptr<T> rtn{ std::make_shared<T>() };

			rtn->m_entity = this->m_self;

			rtn->on_initialize();
			this->m_components.push_back(rtn);

			return rtn;
		}

		template <typename T>
		std::shared_ptr<T> get_component()
		{
			std::vector<std::shared_ptr<Component>>::iterator itr;
			for (itr = this->m_components.begin(); itr != this->m_components.end(); ++itr)
			{
				std::shared_ptr<T> rtn = std::dynamic_pointer_cast<T>(*itr);

				if (rtn)
				{
					return rtn;
				}
			}

			throw std::runtime_error("ERROR::FAILED TO FIND COMPONENT");
		}

		void kill();

		std::shared_ptr<Transform> transform();

		std::shared_ptr<Core> core();

		friend Core;
		friend Window;
	};
}