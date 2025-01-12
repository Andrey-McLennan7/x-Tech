#include <x-Tech/x-Tech.h>

#include <iostream>
#include <ctime>

using namespace xTech;

class Player : public Component
{
private:

	float speed;

public:

	virtual void on_initialize() override
	{
		this->speed = 5.0f;
	}

	virtual void on_tick() override
	{
		// Entity Movement
		vec3 position{ 0.0f };

		if (this->input()->is_key(KEY_W))
		{
			if (this->input()->is_key(KEY_LSHIFT))
			{
				position.z -= speed * this->delta_time();
			}
			else
			{
				position.y += speed * this->delta_time();
			}
		}

		if (this->input()->is_key(KEY_A))
		{
			position.x -= speed * this->delta_time();
		}

		if (this->input()->is_key(KEY_S))
		{
			if (this->input()->is_key(KEY_LSHIFT))
			{
				position.z += speed * this->delta_time();
			}
			else
			{
				position.y -= speed * this->delta_time();
			}
		}

		if (this->input()->is_key(KEY_D))
		{
			position.x += speed * this->delta_time();
		}

		if (this->input()->is_key(KEY_LBRACKET))
		{
			this->scale(vec3{ this->scale() - 0.5f * this->delta_time() });
		}

		if (this->input()->is_key(KEY_RBRACKET))
		{
			this->scale(vec3{ this->scale() + 0.5f * this->delta_time() });
		}

		if (this->input()->is_key(KEY_COMMA))
		{
			this->rotation(vec3{ 0.0f, this->rotation().y - 1.0f * this->delta_time(), 0.0f });
		}
		
		if (this->input()->is_key(KEY_DOT))
		{
			this->rotation(vec3{ 0.0f, this->rotation().y + 1.0f * this->delta_time(), 0.0f });
		}

		this->transform()->move(position);
	}
};

class CameraMover : public Component
{
private:

	float speed;

public:

	virtual void on_initialize() override
	{
		this->speed = 5.0f;
	}

	virtual void on_tick() override
	{
		// Entity Movement
		vec3 position{ 0.0f };

		if (this->input()->is_key(KEY_UP))
		{
			if (this->input()->is_key(KEY_LSHIFT))
			{
				position.z -= speed * this->delta_time();
			}
			else
			{
				position.y += speed * this->delta_time();
			}
		}

		if (this->input()->is_key(KEY_LEFT))
		{
			if (this->input()->is_key(KEY_LSHIFT))
			{
				this->rotation(vec3{ 0.0f, this->rotation().y + 1.0f * this->delta_time(), 0.0f });
			}
			else
			{
				position.x -= speed * this->delta_time();
			}
		}

		if (this->input()->is_key(KEY_DOWN))
		{
			if (this->input()->is_key(KEY_LSHIFT))
			{
				position.z += speed * this->delta_time();
			}
			else
			{
				position.y -= speed * this->delta_time();
			}
		}

		if (this->input()->is_key(KEY_RIGHT))
		{
			if (this->input()->is_key(KEY_LSHIFT))
			{
				this->rotation(vec3{ 0.0f, this->rotation().y - 1.0f * this->delta_time(), 0.0f });
			}
			else
			{
				position.x += speed * this->delta_time();
			}
		}

		if (this->input()->is_key(KEY_COMMA))
		{
			this->rotation(vec3{ 0.0f, this->rotation().y - 1.0f * this->delta_time(), 0.0f });
		}

		if (this->input()->is_key(KEY_DOT))
		{
			this->rotation(vec3{ 0.0f, this->rotation().y + 1.0f * this->delta_time(), 0.0f });
		}

		this->transform()->move(position);
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
	std::shared_ptr<Shader> shader{ core->cache()->load<Shader>("Shader/basic") };
	std::shared_ptr<Shape> shape{ core->cache()->load<Shape>("CUBE") };

	// Create entity 1 and attach components
	std::shared_ptr<Entity> e1{ core->add_entity() };
	std::shared_ptr<ShapeRenderer> e1_renderer{ e1->add_component<ShapeRenderer>() };

	e1_renderer->shader(shader);
	e1_renderer->shape(shape);

	e1->add_component<Player>();
	e1->add_component<BoxCollider>();
	e1->add_component<RigidBody>();

	e1->position(vec3{ 0.0f, 0.0f, -4.0f });

	// Create entity 2 and attach components
	std::shared_ptr<Entity> e2{ core->add_entity() };
	std::shared_ptr<ShapeRenderer> e2_renderer{ e2->add_component<ShapeRenderer>() };

	e2_renderer->shader(shader);
	e2_renderer->shape(shape);

	e2->add_component<BoxCollider>();
	e2->add_component<RigidBody>();

	e2->position(vec3{ 2.0f, 0.0f, -4.0f });

	// Add light
	std::shared_ptr<PointLight> light{ core->add_light() };
	light->direction(light->position() - e1->position());

	std::shared_ptr<Camera> camera{ core->camera(0) };

	camera->entity()->add_component<CameraMover>();

	core->run();

	return 0;
}