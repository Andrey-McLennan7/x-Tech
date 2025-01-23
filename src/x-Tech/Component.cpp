#include "Component.h"

#include "Entity.h"
#include "Core.h"
#include "Window.h"
#include "Transform.h"

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

	std::shared_ptr<Transform> Component::transform() const
	{
		return this->entity()->transform();
	}

	std::shared_ptr<Camera> Component::camera(int index) const
	{
		return this->core()->camera(index);
	}

	void Component::position(const glm::vec3& position)
	{
		this->entity()->position(position);
	}

	void Component::position(float x, float y, float z)
	{
		this->position(glm::vec3{ x, y, z });
	}

	glm::vec3 Component::position() const
	{
		return this->entity()->position();
	}

	void Component::rotation(const glm::vec3& rotation)
	{
		this->entity()->rotation(rotation);
	}

	void Component::rotation(float x, float y, float z)
	{
		this->rotation(glm::vec3{ x, y, z });
	}

	glm::vec3 Component::rotation() const
	{
		return this->entity()->rotation();
	}

	void Component::scale(const glm::vec3& scale)
	{
		this->entity()->scale(scale);
	}

	void Component::scale(float x, float y, float z)
	{
		this->scale(glm::vec3{ x, y, z });
	}

	void Component::scale(float scale)
	{
		this->scale(glm::vec3{ scale });
	}

	glm::vec3 Component::scale() const
	{
		return this->entity()->scale();
	}

	void Component::lock_scale(bool lock)
	{
		this->entity()->lock_scale(lock);
	}

	void Component::name(const std::string& name)
	{
		this->entity()->name(name);
	}

	void Component::name(const char* name)
	{
		this->name(std::string{ name });
	}

	std::string Component::name() const
	{
		return this->entity()->name();
	}

	void Component::tag(const std::string& tag)
	{
		this->entity()->tag(tag);
	}

	void Component::tag(const char* tag)
	{
		this->tag(std::string{ tag });
	}

	std::string Component::tag() const
	{
		return this->entity()->tag();
	}

	float Component::delta_time() const
	{
		return this->window()->delta_time();
	}
}