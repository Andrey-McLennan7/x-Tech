#include "Asteroid.h"

#include "Paths.h"

void Asteroid::random_velocity(float& movement, float& rotation)
{
	movement = (float)(rand() % 6 + 5);

	if (movement > 7.0f)
	{
		rotation = 0.75f;
	}
	else
	{
		rotation = 1.5f;
	}
}

void Asteroid::on_initialize()
{
	this->random_velocity(this->m_movement_speed, this->m_rotation_speed);

	this->m_collider = this->entity()->add_component<BoxCollider>();

	this->m_collider.lock()->size(3.0f);

	std::shared_ptr<ModelRenderer> asteroid_renderer{ this->entity()->add_component<ModelRenderer>() };

	asteroid_renderer->shader(this->cache()->load<Shader>(MODEL_SHADER));
	asteroid_renderer->model(this->cache()->load<Model>(METIORITE_MODEL));

	this->scale(0.05f);

	int x{ 21 }, y{ 25 };
	switch (rand() % 2)
	{
	case 0:
		this->position(glm::vec3((float)(rand() % x + 60), (float)(rand() % y + 1), 0.0f));
		break;
	case 1:
		this->position(glm::vec3((float)(rand() % x + 60), -(float)(rand() % y + 1), 0.0f));
		break;
	}
}

void Asteroid::on_tick()
{
	// Rotate asteroid
	vec3 rotate{ this->rotation() };
	rotate.z += this->m_rotation_speed * this->delta_time();
	this->rotation(rotate);

	// Move asteroid
	vec3 position{ 0.0f };
	position.x -= this->m_movement_speed * this->delta_time();
	this->transform()->move(position);

	// Check asteroid position
	if (this->position().x <= -60.0f)
	{
		this->entity()->kill();
	}
}