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
		this->speed = 50.0f;

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
		if (this->input()->controllers_connected())
		{
			if (this->input()->controller()->left_analogue_in_motion())
			{
				position.x += (this->input()->controller()->left_analogue().x * speed) * this->delta_time();
				position.y += (this->input()->controller()->left_analogue().y * speed) * this->delta_time();
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
		if (this->input()->controllers_connected())
		{
			std::shared_ptr<Controller> controller{ this->input()->controller() };

			if (controller->left_analogue_in_motion())
			{
				std::cout << "Left Joy stick x-axis: " << controller->left_analogue().x << std::endl;
				std::cout << "Left Joy stick y-axis: " << controller->left_analogue().y << std::endl;
			}

			if (controller->is_pressed(CONTROLLER_BUTTON_A))
			{
				std::cout << "Controller button A pressed" << std::endl;
			}

			if (controller->is_pressed(CONTROLLER_BUTTON_B))
			{
				std::cout << "Controller button B pressed" << std::endl;
			}

			if (controller->is_pressed(CONTROLLER_BUTTON_X))
			{
				std::cout << "Controller button X pressed" << std::endl;
			}

			if (controller->is_pressed(CONTROLLER_BUTTON_Y))
			{
				std::cout << "Controller button Y pressed" << std::endl;
			}

			if (controller->is_pressed(CONTROLLER_BUTTON_START))
			{
				std::cout << "Controller button START pressed" << std::endl;
			}

			if (controller->is_pressed(CONTROLLER_BUTTON_BACK))
			{
				std::cout << "Controller button BACK pressed" << std::endl;
			}

			if (controller->is_pressed(CONTROLLER_BUTTON_LSHOULDER))
			{
				std::cout << "Controller button LEFT SHOULDER pressed" << std::endl;
			}

			if (controller->is_pressed(CONTROLLER_BUTTON_RSHOULDER))
			{
				std::cout << "Controller button RIGHT SHOULDER pressed" << std::endl;
			}

			if (controller->is_pressed(CONTROLLER_BUTTON_LSTICK))
			{
				std::cout << "Controller button LEFT STICK pressed" << std::endl;
			}

			if (controller->is_pressed(CONTROLLER_BUTTON_RSTICK))
			{
				std::cout << "Controller button RIGHT STICK pressed" << std::endl;
			}
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

	// Create core and add resources
	std::shared_ptr<Core> core{ Core::initialize() };
	core->add_entity()->add_component<Stop>();
	core->window()->resizable(false);

	float width{ (float)core->window()->size().x };
	float height{ (float)core->window()->size().y };

	// Create entity 1 and attach components
	std::weak_ptr<Entity> e1{ core->add_entity() };
	std::shared_ptr<ModelRenderer> e1_renderer{ e1.lock()->add_component<ModelRenderer>()};
	std::shared_ptr<SoundSource> e1_sound_source{ e1.lock()->add_component<SoundSource>()};

	e1.lock()->name("SpaceShip");
	//e1->add_component<SoundSource>();

	e1_renderer->shader(core->cache()->load<Shader>("Shader/model"));
	e1_renderer->model(core->cache()->load<Model>("Model/FA59AMako/FA59AMako"));
	e1_renderer->attenuation(false);

	e1_sound_source->audio(core->cache()->load<Audio>("Audio/pew"));

	e1->add_component<BoxCollider>();
	e1->add_component<RigidBody>();
	e1->add_component<Player>();

	e1->position(vec3{ 0.0f, 0.0f, -5.0f });

	std::shared_ptr<Entity> e2{ core->add_entity() };
	std::shared_ptr<TextRenderer> gui(e2->add_component<TextRenderer>());

	gui->colour(vec3{ 191.0f / 255.0f });
	gui->shader(core->cache()->load<Shader>("Shader/gui"));
	gui->font(core->cache()->load<Font>("Font/batmfa"));
	gui->text("test");
	gui->position(glm::vec3{ width / 2.0f, height / 2.0f, 0.0f });

	//e2->add_component<ControllerDebug>();

	// Add light
	std::shared_ptr<Entity> light{ core->add_entity() };
	std::shared_ptr<PointLight> light_comp{ light->add_component<PointLight>() };

	// Camera
	core->camera()->entity()->position(vec3{ 0.0f, 0.0f, 50.0f });

	core->run();

	return 0;
}