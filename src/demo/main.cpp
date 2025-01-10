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
		vec3 e_position{ 0.0f };

		if (this->input()->is_key(KEY_W))
		{
			if (this->input()->is_key(KEY_LSHIFT))
			{
				e_position.z -= speed * this->delta_time();
			}
			else
			{
				e_position.y += speed * this->delta_time();
			}
		}

		if (this->input()->is_key(KEY_A))
		{
			e_position.x -= speed * this->delta_time();
		}

		if (this->input()->is_key(KEY_S))
		{
			if (this->input()->is_key(KEY_LSHIFT))
			{
				e_position.z += speed * this->delta_time();
			}
			else
			{
				e_position.y -= speed * this->delta_time();
			}
		}

		if (this->input()->is_key(KEY_D))
		{
			e_position.x += speed * this->delta_time();
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

		this->transform()->move(e_position);

		// Camera movement
		vec3 c_position{ 0.0f };

		if (this->input()->is_key(KEY_UP))
		{
			if (this->input()->is_key(KEY_LSHIFT))
			{
				c_position.z -= this->speed * this->delta_time();
			}
			else
			{
				c_position.y += this->speed * this->delta_time();
			}
		}

		if (this->input()->is_key(KEY_DOWN))
		{
			if (this->input()->is_key(KEY_LSHIFT))
			{
				c_position.z += this->speed * this->delta_time();
			}
			else
			{
				c_position.y -= this->speed * this->delta_time();
			}
		}

		if (this->input()->is_key(KEY_LEFT))
		{
			c_position.x -= this->speed * this->delta_time();
		}

		if (this->input()->is_key(KEY_RIGHT))
		{
			c_position.x += this->speed * this->delta_time();
		}

		this->camera(0)->transform()->move(c_position);
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

	// Create entity and attach components
	std::shared_ptr<Entity> e1{ core->add_entity() };
	std::shared_ptr<ShapeRenderer> e1_renderer{ e1->add_component<ShapeRenderer>() };

	e1_renderer->shader(shader);
	e1_renderer->shape(shape);

	e1->add_component<Player>();

	// Add light
	std::shared_ptr<PointLight> light{ core->add_light() };

	light->direction(light->position() - e1->position());

	core->run();

	return 0;
}