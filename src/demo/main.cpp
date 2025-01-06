#include <x-Tech/x-Tech.h>

#include <iostream>
#include <ctime>

using namespace xTech;

class Player : public Component
{
private:

	float speed;

	std::shared_ptr<Transform> tran;

public:

	virtual void on_initialize() override
	{
		this->speed = 5.0f;
		this->tran = this->transform();
		this->core()->camera()->position(vec3{ 0.0f, 0.0f, 5.0f });
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

		this->tran->move(position);

		// Update shader
		std::shared_ptr<Shader> shader{ this->cache()->load<Shader>("Shader/model") };

		// Vertex shader
		shader->set_mat4("u_Projection", this->core()->camera()->projection_matrix());
		shader->set_mat4("u_View", this->core()->camera()->view_matrix());
		shader->set_mat4("u_Model", this->tran->model_matrix());

		// Fragment shader
		shader->set_vec3("u_ViewPos", this->core()->camera()->transform()->position());
		shader->set_vec3("u_Light.position", vec3{ 0.0f, 20.f, 0.0f });
		shader->set_vec3("u_Light.ambient", vec3{ 0.8f });
		shader->set_vec3("u_Light.diffuse", vec3{ 0.4f });
		shader->set_vec3("u_Light.specular", vec3{ 0.5f });
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
	std::shared_ptr<Shader> shader{ core->cache()->load<Shader>("Shader/model") };
	std::shared_ptr<Model> model{ core->cache()->load<Model>("Model/FA59AMako") };

	// Create entity and attach components
	std::shared_ptr<Entity> ship{ core->add_entity() };

	std::shared_ptr<ModelRenderer> ship_renderer{ ship->add_component<ModelRenderer>() };
	ship_renderer->shader(shader);
	ship_renderer->model(model);

	ship->add_component<Player>();

	core->run();

	return 0;
}