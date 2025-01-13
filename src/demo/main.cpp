#include <x-Tech/x-Tech.h>

#include <iostream>
#include <ctime>

using namespace xTech;

class Stop : public Component
{
public:

	void on_late_tick()
	{
		if (input()->keyboard()->is(KEY_ESC))
		{
			this->core()->end();
		}
	}
};

class Player : public Component
{
private:

	float speed;

	std::shared_ptr<BoxCollider> collider;
	std::shared_ptr<ModelRenderer> renderer;
	std::shared_ptr<SoundSource> sound;

public:

	virtual void on_initialize() override
	{
		this->speed = 5.0f;

		this->collider = this->entity()->get_component<BoxCollider>();
		this->renderer = this->entity()->get_component<ModelRenderer>();
		
		this->sound = this->entity()->get_component<SoundSource>();
	}

	virtual void on_tick() override
	{
		// Keyboard
		vec3 position{ 0.0f };

		if (this->input()->keyboard()->is(KEY_W))
		{
			if (this->input()->keyboard()->is(KEY_LSHIFT))
			{
				position.z -= speed * this->delta_time();
			}
			else
			{
				position.y += speed * this->delta_time();
			}
		}

		if (this->input()->keyboard()->is(KEY_A))
		{
			position.x -= speed * this->delta_time();
		}

		if (this->input()->keyboard()->is(KEY_S))
		{
			if (this->input()->keyboard()->is(KEY_LSHIFT))
			{
				position.z += speed * this->delta_time();
			}
			else
			{
				position.y -= speed * this->delta_time();
			}
		}

		if (this->input()->keyboard()->is(KEY_D))
		{
			position.x += speed * this->delta_time();
		}

		if (this->input()->keyboard()->is(KEY_LBRACKET))
		{
			this->scale(vec3{ this->scale() - 0.5f * this->delta_time() });
		}

		if (this->input()->keyboard()->is(KEY_RBRACKET))
		{
			this->scale(vec3{ this->scale() + 0.5f * this->delta_time() });
		}

		if (this->input()->keyboard()->is(KEY_COMMA))
		{
			this->rotation(vec3{ 0.0f, this->rotation().y - 1.0f * this->delta_time(), 0.0f });
		}
		
		if (this->input()->keyboard()->is(KEY_DOT))
		{
			this->rotation(vec3{ 0.0f, this->rotation().y + 1.0f * this->delta_time(), 0.0f });
		}

		if (this->input()->keyboard()->is_pressed(KEY_SPACE))
		{
			sound->play();
		}

		// Controller
		for (int i{ 0 }; i < this->input()->connected_controllers(); ++i)
		{
			if (this->input()->controller(i)->joy_stick_direction().length() < 0.1f)
			{
				int x = this->input()->controller(i)->joy_stick_direction().x;
				int y = this->input()->controller(i)->joy_stick_direction().y;

				position.x += x * this->speed * this->delta_time();
				position.y += y * this->speed * this->delta_time();
			}
		}

		this->transform()->move(position);
		this->collider->size(this->scale());
	}
};

class ControllerDebug : public Component
{
public:

	virtual void on_tick() override
	{
		for (int i{ 0 }; i < this->input()->connected_controllers(); ++i)
		{
			if (this->input()->controller(i)->joy_stick_direction() != ivec2{ 0 })
			{
				std::cout << "Joy stick x-axis: " << this->input()->controller(i)->joy_stick_direction_x() << std::endl;
				std::cout << "Joy stick y-axis: " << this->input()->controller(i)->joy_stick_direction_y() << std::endl;
			}

			if (this->input()->controller(i)->is_pressed(CONTROLLER_BUTTON_A))
			{
				std::cout << "Controller button A pressed" << std::endl;
			}

			if (this->input()->controller(i)->is_pressed(CONTROLLER_BUTTON_DPAD_UP))
			{
				std::cout << "Controller button DPAD UP pressed" << std::endl;
			}

			if (this->input()->controller(i)->is_pressed(CONTROLLER_BUTTON_DPAD_DOWN))
			{
				std::cout << "Controller button DPAD DOWN pressed" << std::endl;
			}

			if (this->input()->controller(i)->is_pressed(CONTROLLER_BUTTON_DPAD_LEFT))
			{
				std::cout << "Controller button DPAD LEFT pressed" << std::endl;
			}

			if (this->input()->controller(i)->is_pressed(CONTROLLER_BUTTON_DPAD_RIGHT))
			{
				std::cout << "Controller button DPAD RIGHT pressed" << std::endl;
			}
		}
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

		if (this->input()->keyboard()->is(KEY_UP))
		{
			if (this->input()->keyboard()->is(KEY_LSHIFT))
			{
				position.z -= speed * this->delta_time();
			}
			else
			{
				position.y += speed * this->delta_time();
			}
		}

		if (this->input()->keyboard()->is(KEY_LEFT))
		{
			if (this->input()->keyboard()->is(KEY_LSHIFT))
			{
				this->rotation(vec3{ 0.0f, this->rotation().y + 1.0f * this->delta_time(), 0.0f });
			}
			else
			{
				position.x -= speed * this->delta_time();
			}
		}

		if (this->input()->keyboard()->is(KEY_DOWN))
		{
			if (this->input()->keyboard()->is(KEY_LSHIFT))
			{
				position.z += speed * this->delta_time();
			}
			else
			{
				position.y -= speed * this->delta_time();
			}
		}

		if (this->input()->keyboard()->is(KEY_RIGHT))
		{
			if (this->input()->keyboard()->is(KEY_LSHIFT))
			{
				this->rotation(vec3{ 0.0f, this->rotation().y - 1.0f * this->delta_time(), 0.0f });
			}
			else
			{
				position.x += speed * this->delta_time();
			}
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
	core->add_entity()->add_component<Stop>();

	// Create entity 1 and attach components
	std::shared_ptr<Entity> e1{ core->add_entity() };
	std::shared_ptr<ModelRenderer> e1_renderer{ e1->add_component<ModelRenderer>() };
	std::shared_ptr<SoundSource> e1_sound_source{ e1->add_component<SoundSource>() };

	e1_renderer->shader(core->cache()->load<Shader>("Shader/model"));
	e1_renderer->model(core->cache()->load<Model>("Model/FA59AMako/FA59AMako"));
	e1_renderer->attenuation(false);

	e1_sound_source->audio(core->cache()->load<Audio>("Audio/pew"));

	e1->add_component<BoxCollider>();
	e1->add_component<RigidBody>();
	e1->add_component<Player>();

	e1->position(vec3{ 0.0f, 0.0f, -5.0f });

	// Add light
	std::shared_ptr<Entity> light{ core->add_entity() };
	std::shared_ptr<PointLight> light_comp{ light->add_component<PointLight>() };

	// Camera
	core->camera()->entity()->add_component<CameraMover>();
	core->camera()->entity()->position(vec3{ 0.0f, 0.0f, 50.0f });

	core->run();

	return 0;
}