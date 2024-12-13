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
		vec3 position{ 0.0f };

		if (input()->is_key(KEY_W))
		{
			if (input()->is_key(KEY_LSHIFT))
			{
				position.z -= speed * this->delta_time();
			}
			else
			{
				position.y += speed * this->delta_time();
			}
		}

		if (input()->is_key(KEY_A))
		{
			position.x -= speed * this->delta_time();
		}

		if (input()->is_key(KEY_S))
		{
			if (input()->is_key(KEY_LSHIFT))
			{
				position.z += speed * this->delta_time();
			}
			else
			{
				position.y -= speed * this->delta_time();
			}
		}

		if (input()->is_key(KEY_D))
		{
			position.x += speed * this->delta_time();
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
	std::shared_ptr<Shader> shaders{ core->cache()->load<Shader>("Shader/basic") };
	std::shared_ptr<Audio> audio{ core->cache()->load<Audio>("Audio/dixie_horn") };

	// Create entity 1 and attach components
	std::shared_ptr<Entity> entity1{ core->add_entity() };

	entity1->add_component<TriangleRenderer>();
	entity1->add_component<BoxCollider>();
	entity1->add_component<RigidBody>();
	entity1->add_component<Entity1Mover>();

	std::shared_ptr<SoundSource> sound{ entity1->add_component<SoundSource>() };

	sound->audio(audio);

	sound->play();

	core->run();

	return 0;
}