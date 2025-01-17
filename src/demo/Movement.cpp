#include "Movement.h"
#include "Controls.h"

void Movement::on_initialize()
{
	this->m_speed = 0.0f;
	this->m_end_point = 0.0f;
}

void Movement::on_tick()
{
	vec3 position{ this->position() };

	position.x -= this->m_speed * this->delta_time();

	if (position.x <= -this->m_end_point)
	{
		position.x = this->m_end_point;
	}

	this->position(position);
}

void Movement::speed(float speed)
{
	this->m_speed = speed;
}

float Movement::speed() const
{
	return this->m_speed;
}

void Movement::end_point(float point)
{
	this->m_end_point = point;
}

float Movement::end_point() const
{
	return this->m_end_point;
}