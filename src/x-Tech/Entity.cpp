#include "Entity.h"

namespace xTech
{
	void Entity::tick()
	{
		for (size_t ci{ 0 }; ci < this->m_components.size(); ++ci)
		{
			//this->m_components.at(ci)->tick();
		}
	}

	void Entity::display()
	{
		for (size_t ci{ 0 }; ci < this->m_components.size(); ++ci)
		{
			//this->m_components.at(ci)->display();
		}
	}

	void Entity::kill()
	{
		if (!m_alive) return;

		m_alive = false;

		for (size_t ci{ 0 }; ci < this->m_components.size(); ++ci)
		{
			//this->m_components.at(ci)->kill();
		}
	}
}