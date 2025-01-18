#include "Bullet.h"
#include "Paths.h"

void Bullet::on_initialize()
{
	this->m_collider = entity()->add_component<BoxCollider>();
	this->m_collider.lock()->size(this->scale());

	this->m_explosion = this->entity()->add_component<SoundSource>();
	this->m_explosion.lock()->audio(EXPLOSION_AUDIO);

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

	std::vector<std::shared_ptr<Collider>> colliders;
	this->core()->find<Collider>(colliders);

	std::vector<std::shared_ptr<Collider>>::iterator itr;
	for (itr = colliders.begin(); itr != colliders.end(); ++itr)
	{
		if (this->m_collider.lock()->on_collision(*(*itr)))
		{
			if ((*itr)->tag() == ENEMY)
			{
				this->m_explosion.lock()->play();

				(*itr)->entity()->kill();
				this->entity()->kill();
			}
		}
	}
}