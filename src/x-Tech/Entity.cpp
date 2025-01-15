#include "Entity.h"
#include "Core.h"
#include "Component.h"
#include "Window.h"
#include "Transform.h"

#include <SDL2/SDL.h>

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

	void Entity::gui()
	{
		std::vector<std::shared_ptr<Component>>::iterator itr;
		for (itr = this->m_components.begin(); itr != this->m_components.end(); ++itr)
		{
			(*itr)->gui();
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

	void Entity::position(const glm::vec3& position)
	{
		this->m_transform.lock()->position(position);
	}

	glm::vec3 Entity::position() const
	{
		return this->m_transform.lock()->position();
	}

	void Entity::rotation(const glm::vec3& rotation)
	{
		this->m_transform.lock()->rotation(rotation);
	}

	glm::vec3 Entity::rotation() const
	{
		return this->m_transform.lock()->rotation();
	}

	void Entity::scale(const glm::vec3& scale)
	{
		this->m_transform.lock()->scale(scale);
	}

	glm::vec3 Entity::scale() const
	{
		return this->m_transform.lock()->scale();
	}

	void Entity::lock_scale(bool lock)
	{
		this->m_transform.lock()->lock_scale(lock);
	}

	void Entity::name(const std::string& name)
	{
		// Check if 'name' matches the names of other entities in core
		std::vector<std::shared_ptr<Entity>>::const_iterator itr;
		for (itr = this->core()->m_entities.begin(); itr != this->core()->m_entities.end(); ++itr)
		{
			// Ignore self
			if ((*itr)->m_self.lock() == this->m_self.lock())
			{
				continue;
			}

			// Compare names
			if (name == (*itr)->m_name)
			{
				throw std::runtime_error("ERROR::ENTITY NAMES CANNOT MATCH");
			}
		}

		// Check if there is any space between words in 'name'
		// all names should be ONE word
		int(*IsSpace)(int) = std::isspace;
		if (std::find_if(name.begin(), name.end(), IsSpace) != name.end())
		{
			throw std::runtime_error("ERROR::\'" + name + "\' SHOULD BE ONE WORD");
		}

		// Assign different name
		this->m_name = name;
	}

	std::string Entity::name() const
	{
		return this->m_name;
	}
}