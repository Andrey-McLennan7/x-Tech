#include <x-Tech/x-Tech.h>

#include <iostream>
#include <ctime>

using namespace xTech;

class Player : public Component
{
private:

	float speed;

	std::shared_ptr<Shader> m_shader;

	std::shared_ptr<Camera> m_camera;

public:

	virtual void on_initialize() override
	{
		this->speed = 5.0f;

		this->m_shader = this->cache()->load<Shader>("Shader/model");
		this->m_camera = this->core()->camera(0);
	}

	virtual void on_tick() override
	{
		// Movement
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
			std::cout << this->rotation().y << std::endl;
		}
		
		if (this->input()->is_key(KEY_DOT))
		{
			this->rotation(vec3{ 0.0f, this->rotation().y + 1.0f * this->delta_time(), 0.0f });
			std::cout << this->rotation().y << std::endl;
		}

		if (this->input()->is_key(KEY_UP))
		{
			if (this->input()->is_key(KEY_LSHIFT))
			{
				this->m_camera->position(vec3{ 0.0f, 0.0f, this->m_camera->position().z - this->speed * this->delta_time() });
			}
			else
			{
				this->m_camera->position(vec3{ 0.0f, this->m_camera->position().y + this->speed * this->delta_time(), 0.0f });
			}
		}

		if (this->input()->is_key(KEY_DOWN))
		{
			if (this->input()->is_key(KEY_LSHIFT))
			{
				this->m_camera->position(vec3{ 0.0f, 0.0f, this->m_camera->position().z + this->speed * this->delta_time() });
			}
			else
			{
				this->m_camera->position(vec3{ 0.0f, this->m_camera->position().y - this->speed * this->delta_time(), 0.0f });
			}
		}

		if (this->input()->is_key(KEY_LEFT))
		{
			this->m_camera->position(vec3{ this->m_camera->position().x - this->speed * this->delta_time(), 0.0f, 0.0f });
		}

		if (this->input()->is_key(KEY_RIGHT))
		{
			this->m_camera->position(vec3{ this->m_camera->position().x + this->speed * this->delta_time(), 0.0f, 0.0f });
		}

		if (this->input()->is_button(MOUSE_RIGHT))
		{
			std::cout << "Right click" << std::endl;
		}

		if (this->input()->is_button_pressed(MOUSE_LEFT))
		{
			std::cout << "Left click" << std::endl;
		}

		if (this->input()->is_button_released(MOUSE_MIDDLE))
		{
			std::cout << "Middle click" << std::endl;
		}

		if (this->input()->wheel() > 0)
		{
			std::cout << "Mouse wheel " << this->input()->wheel() << std::endl;
		}
		else if (this->input()->wheel() < 0)
		{
			std::cout << "Mouse wheel " << this->input()->wheel() << std::endl;
		}

		if (this->input()->in_motion())
		{
			std::cout << "Cursor: " << this->input()->cursor().x << ' ' << this->input()->cursor().y << std::endl;
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
	std::shared_ptr<Shape> cube_model{ core->cache()->load<Shape>("CUBE") };

	// Create entity and attach components
	std::shared_ptr<Entity> cube{ core->add_entity() };

	std::shared_ptr<ShapeRenderer> cube_renderer{ cube->add_component<ShapeRenderer>() };

	cube_renderer->shader(shader);
	cube_renderer->shape(cube_model);

	cube->add_component<Player>();

	core->run();

	return 0;
}