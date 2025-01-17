#include "Star.h"

#include "Paths.h"

Star::Star() :
	m_speed{ 0.0f }
{}

void Star::on_initialize()
{
	this->m_speed = 10.0f;

	std::shared_ptr<ShapeRenderer> star_renderer{ entity()->add_component<ShapeRenderer>()};

	star_renderer->shader(cache()->load<Shader>(BASIC_SHADER));
	star_renderer->shape(cache()->load<Shape>(QUAD_SHAPE));

	this->scale(0.5f);

	int x{ 110 }, y{ 200 };
	float z{ -49.9f };
	switch (rand() % 4)
	{
	case 0:
		this->position(vec3{ (float)(rand() % x), (float)(rand() % y), z });
		break;
	case 1:
		this->position(vec3{ -(float)(rand() % x), (float)(rand() % y), z });
		break;
	case 2:
		this->position(vec3{ -(float)(rand() % x), -(float)(rand() % y), z });
		break;
	case 3:
		this->position(vec3{ (float)(rand() % x), -(float)(rand() % y), z });
		break;
	}
}

void Star::on_tick()
{
	vec3 position{ this->position()};

	position.x -= this->m_speed * this->delta_time();

	if (position.x <= -110.0f)
	{
		position.x = 110.0f;
	}

	this->position(position);
}