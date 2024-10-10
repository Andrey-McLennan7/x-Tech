#include <memory>
#include <vector>

namespace xTech
{
	class Core;
	class Component;

	class Entity
	{
	private:

		std::weak_ptr<Core> m_core;
		std::vector<std::shared_ptr<Component>> m_components;

	public:

		~Entity();

		template <typename T>
		std::shared_ptr<T> add_component()
		{
			std::shared_ptr<T> rtn{ std::make_shared<T>() };

			this->m_components.push_back(rtn);

			return rtn;
		}

		friend Core;
	};
}