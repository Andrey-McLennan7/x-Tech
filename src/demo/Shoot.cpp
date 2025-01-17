#include "Shoot.h"
#include "Bullet.h"

void Shoot::shoot()
{
	std::shared_ptr<Entity> bullet{ this->core()->add_entity() };

	bullet->add_component<Bullet>();
}