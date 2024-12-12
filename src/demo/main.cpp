#include <x-Tech/x-Tech.h>

#include <iostream>
#include <ctime>

using namespace xTech;

class Entity1Mover : public Component
{
private:

	float speed;

public:

	virtual void on_initialize() override
	{
		speed = 5.0f;
	}

	virtual void on_tick() override
	{
		float deltaTime{ core()->window()->delta_time() };

		vec3 position{ 0.0f };

		// Read keyboard input
		const Uint8* state{ SDL_GetKeyboardState(NULL) };

		if (state[SDL_SCANCODE_W])
		{
			if (state[SDL_SCANCODE_LSHIFT])
			{
				position.z -= speed * deltaTime;
			}
			else
			{
				position.y += speed * deltaTime;
			}
		}

		if (state[SDL_SCANCODE_A])
		{
			position.x -= speed * deltaTime;
		}

		if (state[SDL_SCANCODE_S])
		{
			if (state[SDL_SCANCODE_LSHIFT])
			{
				position.z += speed * deltaTime;
			}
			else
			{
				position.y -= speed * deltaTime;
			}
		}

		if (state[SDL_SCANCODE_D])
		{
			position.x += speed * deltaTime;
		}

		transform()->move(position);
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

	// Create core and add resources
	std::shared_ptr<Core> core{ Core::initialize() };
	std::shared_ptr<Shader> triangle_shader{ core->cache()->load<Shader>("Shader/basic") };
	std::shared_ptr<Audio> triangle_audio{ core->cache()->load<Audio>("Audio/dixie_horn") };

	// Create entity 1 and attach components
	std::shared_ptr<Entity> entity1{ core->add_entity() };

	entity1->add_component<TriangleRenderer>();
	entity1->add_component<BoxCollider>();
	entity1->add_component<RigidBody>();
	entity1->add_component<Entity1Mover>();

	core->run();

	return 0;
}