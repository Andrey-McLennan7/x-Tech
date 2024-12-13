#include "Component.h"

#include "Entity.h"
#include "Core.h"
#include "Window.h"

namespace xTech
{
	void Component::fixed_tick()
	{
		this->on_fixed_tick();
	}

	void Component::tick()
	{
		this->on_tick();
	}

	void Component::late_tick()
	{
		this->on_late_tick();
	}

	void Component::display()
	{
		this->on_display();
	}

	void Component::gui()
	{
		this->on_gui();
	}

	void Component::kill()
	{
		this->m_alive = false;
	}

	void Component::on_initialize() {}

	void Component::on_fixed_tick() {}
	void Component::on_tick()		{}
	void Component::on_late_tick()  {}

	void Component::on_display()	{}
	void Component::on_gui()		{}

	std::shared_ptr<Entity> Component::entity() const
	{
		return this->m_entity.lock();
	}

	std::shared_ptr<Transform> Component::transform() const
	{
		return this->entity()->transform();
	}

	std::shared_ptr<Core> Component::core() const
	{
		return this->entity()->core();
	}

	std::shared_ptr<Window> Component::window() const
	{
		return this->core()->window();
	}

	std::shared_ptr<Cache> Component::cache() const
	{
		return this->core()->cache();
	}

	std::shared_ptr<Input> Component::input() const
	{
		return this->core()->input();
	}

	float Component::delta_time() const
	{
		return this->window()->delta_time();
	}
}