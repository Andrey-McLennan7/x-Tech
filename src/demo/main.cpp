#include <x-Tech/x-Tech.h>

#include "Controls.h"
#include "Movement.h"
#include "Data.h"
#include "Rotator.h"
#include "CollisionResponce.h"

#include <iostream>
#include <ctime>

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
	srand(time(0));

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
	std::shared_ptr<Shape> star_shape{ core->cache()->load<Shape>("QUAD") };

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
	player->add_component<Controls>();
	player->add_component<Data>();

	player->rotation(vec3{ 0.0f, 1.5f, 0.0f });
	player->scale(0.1f);
	player->name("Player");

	player_renderer->shader(model_shader);
	player_renderer->model(ship_model);

	player_sound->audio(shoot_sound);

	// Asteroids
	//for (int i{ 0 }; i < 20; ++i)
	//{
	//	std::shared_ptr<Entity> asteroid{ core->add_entity() };
	//
	//	int x{ 21 }, y{ 25 };
	//	switch (rand() % 2)
	//	{
	//	case 0:
	//		asteroid->position(glm::vec3((float)(rand() % x + 60), (float)(rand() % y + 1), 0.0f));
	//		break;
	//	case 1:
	//		asteroid->position(glm::vec3((float)(rand() % x + 60), -(float)(rand() % y + 1), 0.0f));
	//		break;
	//	}
	//
	//	std::shared_ptr<ModelRenderer> asteroid_renderer{ asteroid->add_component<ModelRenderer>() };
	//
	//	asteroid_renderer->shader(model_shader);
	//	asteroid_renderer->model(asteroid_model);
	//
	//	std::shared_ptr<Movement> asteroid_movement{ asteroid->add_component<Movement>() };
	//
	//	asteroid->add_component<BoxCollider>();
	//
	//	asteroid->scale(0.05f);
	//	asteroid->name("Asteroid");
	//}

	// Stars
	for (int i{ 0 }; i < 2000; ++i)
	{
		std::shared_ptr<Entity> star{ core->add_entity() };

		int x{ 110 }, y{ 200 };
		float z{ -49.9f };
		switch (rand() % 4)
		{
		case 0:
			star->position(vec3{ (float)(rand() % x), (float)(rand() % y), z });
			break;
		case 1:
			star->position(vec3{ -(float)(rand() % x), (float)(rand() % y), z });
			break;
		case 2:
			star->position(vec3{ -(float)(rand() % x), -(float)(rand() % y), z });
			break;
		case 3:
			star->position(vec3{ (float)(rand() % x), -(float)(rand() % y), z });
			break;
		}

		star->scale(0.5f);

		std::shared_ptr<ShapeRenderer> star_renderer{ star->add_component<ShapeRenderer>() };

		star_renderer->shader(basic_shader);
		star_renderer->shape(star_shape);

		std::shared_ptr<Movement> star_movement{ star->add_component<Movement>() };

		star_movement->speed(10.0f);
		star_movement->end_point(110.0f);

		star->name("Star" + std::to_string(i));
	}

	// Adjust the default camera
	std::shared_ptr<Camera> camera{ core->camera() };

	camera->position(vec3{ 0.0f, 0.0f, 50.0f });

	// Prevent the window from being resized
	core->window()->resizable(false);

	// Run engine
	core->run();

	return 0;
}