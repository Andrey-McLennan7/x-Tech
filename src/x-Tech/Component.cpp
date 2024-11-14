#include "Component.h"

#include "Entity.h"
#include "Core.h"
#include "Window.h"

namespace xTech
{
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

	std::shared_ptr<Entity> Component::entity()
	{
		return this->m_entity.lock();
	}

	std::shared_ptr<Core> Component::core()
	{
		return this->entity()->core();
	}

	std::shared_ptr<Window> Component::window()
	{
		return this->core()->window();
	}
}