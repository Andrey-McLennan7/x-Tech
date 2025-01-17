#include "Player.h"

#include "Paths.h"

#include "Shoot.h"
#include "Controls.h"
#include "CollisionResponce.h"

#include <sstream>
#include <iostream>
#include <iomanip>

void Player::on_initialize()
{
	// Initiate player
	this->m_health = 100.0f;
	this->m_distance = 0.0f;

	this->m_collider = entity()->add_component<BoxCollider>();

	std::shared_ptr<ModelRenderer> player_renderer{ entity()->add_component<ModelRenderer>() };
	std::shared_ptr<SoundSource> player_sound{ entity()->add_component<SoundSource>() };

	player_renderer->shader(this->cache()->load<Shader>(MODEL_SHADER));
	player_renderer->model(this->cache()->load<Model>(SHIP_MODEL));

	player_sound->audio(this->cache()->load<Audio>(PEW_AUDIO));

	entity()->add_component<Shoot>();
	entity()->add_component<CollisionResponce>();
	entity()->add_component<Controls>();

	this->rotation(vec3{ 0.0f, 1.5f, 0.0f });
	this->scale(0.1f);
	this->name("Player");

	// Add GUI health
	this->m_gui_health = core()->add_entity()->add_component<TextRenderer>();

	this->m_gui_health.lock()->font(BATMFA_FONT);
	this->m_gui_health.lock()->shader(GUI_SHADER);

	this->m_gui_health.lock()->position(vec3{ 25.0f, core()->window()->size().y - 50.0f, 0.0f});
	this->m_gui_health.lock()->scale(0.7f);

	// Add GUI distance
	this->m_gui_distance = core()->add_entity()->add_component<TextRenderer>();

	this->m_gui_distance.lock()->font(BATMFA_FONT);
	this->m_gui_distance.lock()->shader(GUI_SHADER);

	this->m_gui_distance.lock()->position(vec3{ 25.0f, core()->window()->size().y - 100.0f, 0.0f });
	this->m_gui_distance.lock()->scale(0.7f);
}

void Player::on_tick()
{
	this->m_distance += 2.5f * this->delta_time();

	std::stringstream stream1;
	std::stringstream stream2;

	stream1 << std::fixed << "Health: " << std::setprecision(2) << this->m_health;
	stream2 << std::fixed << "Distance: " << std::setprecision(2) << this->m_distance;

	this->m_gui_health.lock()->text(stream1.str());
	this->m_gui_distance.lock()->text(stream2.str());

	// Check health condition
	if (this->m_health <= 0.00000001f)
	{
		system("cls");
		std::cout << "GAME OVER\n" << std::endl;
		system("pause");

		this->core()->end();
	}
}