#include <x-Tech/x-Tech.h>
#include <iostream>

using namespace xTech;

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

	// Load resources
	// Shaders
	std::shared_ptr<Shader> model_shader{ core->cache()->load<Shader>("Shader/model") };
	std::shared_ptr<Shader> basic_shader{ core->cache()->load<Shader>("Shader/basic") };
	std::shared_ptr<Shader> gui_shader{ core->cache()->load<Shader>("Shader/gui") };

	// Models
	std::shared_ptr<Model> asteroid_model{ core->cache()->load<Model>("Model/FA59AMako/FA59AMako") };
	std::shared_ptr<Model> ship_model{ core->cache()->load<Model>("Model/Meteorite/NHMW-MIN-J2669-Nakhla_low_res") };

	// Shapes
	std::shared_ptr<Shape> bullet_shape{ core->cache()->load<Shape>("QUAD") };
	std::shared_ptr<Shape> star_shape{ core->cache()->load<Shape>("CUBE") };

	// Fonts
	std::shared_ptr<Font> font{ core->cache()->load<Font>("Font/batmfa") };

	// Prevent the window from being resized
	core->window()->resizable(false);

	// Run engine
	core->run();

	return 0;
}