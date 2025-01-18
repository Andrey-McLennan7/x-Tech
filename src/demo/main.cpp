#include <x-Tech/x-Tech.h>

#include "Paths.h"

#include "Player.h"
#include "AsteroidSpawner.h"
#include "Star.h"

#include <iostream>
#include <ctime>

using namespace xTech;

class BackgroundInitialiser : public Component
{
public:

	virtual void on_initialize() override
	{
		std::shared_ptr<SoundSource> background_audio{ this->core()->add_entity()->add_component<SoundSource>() };

		background_audio->audio(BACKGROUND_AUDIO);
		background_audio->loop(true);

	}

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
	core->add_entity()->add_component<BackgroundInitialiser>();

	/* Load resources */
	// Shaders
	core->cache()->load<Shader>(MODEL_SHADER);
	core->cache()->load<Shader>(BASIC_SHADER);
	core->cache()->load<Shader>(GUI_SHADER);

	// Models
	core->cache()->load<Model>(METIORITE_MODEL);
	core->cache()->load<Model>(SHIP_MODEL);

	// Shapes
	core->cache()->load<Shape>(QUAD_SHAPE);
	core->cache()->load<Shape>(CUBE_SHAPE);

	// Fonts
	core->cache()->load<Font>(BATMFA_FONT);

	// Audio
	core->cache()->load<Audio>(BACKGROUND_AUDIO);
	core->cache()->load<Audio>(EXPLOSION_AUDIO);
	core->cache()->load<Audio>(PEW_AUDIO);
	core->cache()->load<Audio>(HIT_AUDIO);

	/* Adding entities */
	// Add player
	core->add_entity()->add_component<Player>();

	// Add asteroid spawner
	core->add_entity()->add_component<AsteroidSpawner>();

	// Add stars
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