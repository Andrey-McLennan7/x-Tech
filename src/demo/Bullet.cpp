#include "Bullet.h"

#include "Paths.H"

void Bullet::on_initialize()
{
	std::shared_ptr<ShapeRenderer> renderer{ entity()->add_component<ShapeRenderer>() };

	renderer->shader(core()->cache()->load<Shader>(BASIC_SHADER));
	renderer->shape(core()->cache()->load<Shape>(CUBE_SHAPE));
	renderer->colour(vec3{ 0.0f, 0.0f, 255.0f });

	this->position(this->core()->get_entity_by_name("Player")->position() + vec3{5.0f, 0.0f, 0.0f});
}

void Bullet::on_tick()
{
	vec3 position{ 0.0f };

	position.x += 50.0f * this->delta_time();

	this->transform()->move(position);

	if (this->position().x >= 60.0f)
	{
		this->entity()->kill();
	}
}