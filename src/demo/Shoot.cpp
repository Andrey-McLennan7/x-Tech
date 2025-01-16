#include "Shoot.h"

#include <x-Tech/x-Tech.h>

std::shared_ptr<Entity> Shoot::generate_bullet_entity()
{
	std::shared_ptr<Entity> rtn{ std::make_shared<Entity>() };

	std::shared_ptr<BoxCollider> collider{ rtn->add_component<BoxCollider>() };
	std::shared_ptr<ShapeRenderer> renderer{ rtn->add_component<ShapeRenderer>() };

	collider->size(rtn->scale());

	return std::shared_ptr<Entity>();
}

void Shoot::on_initialize()
{
	this->m_model = this->core()->cache()->load<Shape>("CUBE");
}

void Shoot::on_tick()
{
	Component::on_tick();
}

void Shoot::shoot()
{
	this->m_bullets;
}