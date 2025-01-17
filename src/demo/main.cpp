#include <x-Tech/x-Tech.h>

#include "Player.h"
#include "Star.h"

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
	core->cache()->load<Shader>("Shader/model");
	core->cache()->load<Shader>("Shader/basic");
	core->cache()->load<Shader>("Shader/gui");

	// Models
	core->cache()->load<Model>("Model/Meteorite/NHMW-MIN-J2669-Nakhla_low_res");
	core->cache()->load<Model>("Model/FA59AMako/FA59AMako");

	// Shapes
	core->cache()->load<Shape>("QUAD");

	// Fonts
	core->cache()->load<Font>("Font/batmfa");

	// Audio
	core->cache()->load<Audio>("Audio/pew");

	/* Adding entities */
	// Add player
	core->add_entity()->add_component<Player>();

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
	//	asteroid_renderer->shader(model_shader.lock());
	//	asteroid_renderer->model(asteroid_model.lock());
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
		core->add_entity()->add_component<Star>();
	}

	// Adjust the default camera
	std::weak_ptr<Camera> camera{ core->camera() };

	camera.lock()->position(vec3{ 0.0f, 0.0f, 50.0f });

	// Prevent the window from being resized
	core->window()->resizable(false);

	// Run engine
	core->run();

	return 0;
}