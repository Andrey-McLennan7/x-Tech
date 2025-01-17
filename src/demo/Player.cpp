#include "Player.h"

#include "Shoot.h"
#include "Controls.h"
#include "CollisionResponce.h"

#include <iostream>

void Player::on_initialize()
{
	this->m_health = 100.0f;
	this->m_distance = 0.0f;

	std::shared_ptr<ModelRenderer> player_renderer{ entity()->add_component<ModelRenderer>() };
	std::shared_ptr<SoundSource> player_sound{ entity()->add_component<SoundSource>() };

	player_renderer->shader(this->cache()->load<Shader>("Shader/model"));
	player_renderer->model(this->cache()->load<Model>("Model/FA59AMako/FA59AMako"));

	player_sound->audio(this->cache()->load<Audio>("Audio/pew"));

	entity()->add_component<BoxCollider>();

	entity()->add_component<Shoot>();
	entity()->add_component<CollisionResponce>();
	entity()->add_component<Controls>();

	this->rotation(vec3{ 0.0f, 1.5f, 0.0f });
	this->scale(0.1f);
	this->name("Player");
}

void Player::on_tick()
{
	this->m_distance += 2.5f * this->delta_time();

	// Check health condition
	if (this->m_health <= 0.00000001f)
	{
		system("cls");
		std::cout << "GAME OVER\n" << std::endl;
		system("pause");

		this->core()->end();
	}
}