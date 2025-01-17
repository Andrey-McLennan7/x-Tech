#include "AsteroidSpawner.h"

#include "Player.h"
#include "Asteroid.h"

void AsteroidSpawner::on_initialize()
{
	this->m_timer = 0.0f;
	this->m_player = this->core()->get_entity_by_name("Player")->get_component<Player>();
}

void AsteroidSpawner::on_tick()
{
	this->m_timer -= this->delta_time();

	if (this->m_timer <= 0.0f)
	{
		this->core()->add_entity()->add_component<Asteroid>();
		this->m_timer = (float)(rand() % 3 + 1);
	}
}