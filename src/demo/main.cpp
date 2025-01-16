#include <x-Tech/x-Tech.h>

#include "Controls.h"
#include "Movement.h"
#include "Shoot.h"
#include "Data.h"
#include "Rotator.h"
#include "CollisionResponce.h"

#include <iostream>

using namespace xTech;

class Quit : public Component
{
public:

	virtual void on_tick() override
	{
		if (this->input()->keyboard()->is_pressed(KEY_ESC))
		{
			this->core()->end();
		}
	}
};

int safe_main();

int main()
{
	try
	{
		safe_main();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}

int safe_main()
{
	// Create core
	std::shared_ptr<Core> core{ Core::initialize() };

	// Add quit option on ESCAPE key
	core->add_entity()->add_component<Quit>();



	/* Load resources */
	// Shaders
	std::shared_ptr<Shader> model_shader{ core->cache()->load<Shader>("Shader/model") };
	std::shared_ptr<Shader> basic_shader{ core->cache()->load<Shader>("Shader/basic") };
	std::shared_ptr<Shader> gui_shader{ core->cache()->load<Shader>("Shader/gui") };

	// Models
	std::shared_ptr<Model> asteroid_model{ core->cache()->load<Model>("Model/Meteorite/NHMW-MIN-J2669-Nakhla_low_res") };
	std::shared_ptr<Model> ship_model{ core->cache()->load<Model>("Model/FA59AMako/FA59AMako") };

	// Shapes
	std::shared_ptr<Shape> bullet_shape{ core->cache()->load<Shape>("QUAD") };
	std::shared_ptr<Shape> star_shape{ core->cache()->load<Shape>("CUBE") };

	// Fonts
	std::shared_ptr<Font> font{ core->cache()->load<Font>("Font/batmfa") };

	// Audio
	std::shared_ptr<Audio> shoot_sound{ core->cache()->load<Audio>("Audio/pew")};



	/* Adding entities */
	// Add player
	std::shared_ptr<Entity> player{ core->add_entity() };

	std::shared_ptr<ModelRenderer> player_renderer{ player->add_component<ModelRenderer>() };
	std::shared_ptr<SoundSource> player_sound{ player->add_component<SoundSource>() };

	player->add_component<BoxCollider>();

	player->add_component<CollisionResponce>();
	player->add_component<Shoot>();
	player->add_component<Controls>();
	player->add_component<Data>();

	player->rotation(vec3{ 0.0f, 1.5f, 0.0f });
	player->scale(0.1f);

	player_renderer->shader(model_shader);
	player_renderer->model(ship_model);

	player_sound->audio(shoot_sound);

	// Asteroid
	std::shared_ptr<Entity> asteroid{ core->add_entity() };

	asteroid->scale(0.05f);

	// Add asteroid components
	std::shared_ptr<ModelRenderer> asteroid_renderer{ asteroid->add_component<ModelRenderer>() };

	asteroid_renderer->shader(model_shader);
	asteroid_renderer->model(asteroid_model);

	// Adjust the default camera
	std::shared_ptr<Camera> camera{ core->camera() };

	camera->position(vec3{ 0.0f, 0.0f, 50.0f });

	// Prevent the window from being resized
	core->window()->resizable(false);

	// Run engine
	core->run();

	return 0;
}