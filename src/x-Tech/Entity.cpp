#include <SDL2/SDL.h>

#include "Core.h"
#include "Entity.h"
#include "Component.h"

#include "Window.h"

namespace xTech
{
	void Entity::fixed_tick()
	{
		std::vector<std::shared_ptr<Component>>::iterator itr;
		for (itr = this->m_components.begin(); itr != this->m_components.end(); ++itr)
		{
			(*itr)->fixed_tick();
		}
	}

	void Entity::tick()
	{
		std::vector<std::shared_ptr<Component>>::iterator itr;
		for (itr = this->m_components.begin(); itr != this->m_components.end(); ++itr)
		{
			(*itr)->tick();
		}
	}

	void Entity::late_tick()
	{
		std::vector<std::shared_ptr<Component>>::iterator itr;
		for (itr = this->m_components.begin(); itr != this->m_components.end(); ++itr)
		{
			(*itr)->late_tick();
		}
	}

	void Entity::display()
	{
		std::vector<std::shared_ptr<Component>>::iterator itr;
		for (itr = this->m_components.begin(); itr != this->m_components.end(); ++itr)
		{
			(*itr)->display();
		}
	}

	void Entity::kill()
	{
		if (!this->m_alive) return;

		this->m_alive = false;

		std::vector<std::shared_ptr<Component>>::iterator itr;
		for (itr = this->m_components.begin(); itr != this->m_components.end(); ++itr)
		{
			(*itr)->kill();
		}
	}

	std::shared_ptr<Transform> Entity::transform()
	{
		return this->m_transform.lock();
	}

	std::shared_ptr<Core> Entity::core()
	{
		return this->m_core.lock();
	}
}