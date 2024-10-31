#include "Component.h"

namespace xTech
{
	void Component::on_initialize() {}
	void Component::on_tick()       {}
	void Component::on_display()    {}
	
	void Component::tick()
	{
		this->on_tick();
	}

	void Component::display()
	{
		this->on_display();
	}

	void Component::kill()
	{
		this->m_alive = false;
	}

	std::shared_ptr<Entity> Component::get_entity()
	{
		return this->m_entity.lock();
	}
}