#include "Controls.h"

void Controls::on_initialize()
{
	this->m_speed = 25.0f;

	this->m_sound = this->entity()->get_component<SoundSource>();
}

void Controls::on_tick()
{
	vec3 position{ 0.0f };

	if (this->input()->keyboard()->is(KEY_W) && this->position().y <= 25.0f)
	{
		position.y += this->m_speed * this->delta_time();
	}

	if (this->input()->keyboard()->is(KEY_S) && this->position().y >= -25.0f)
	{
		position.y -= this->m_speed * this->delta_time();
	}

	if (this->input()->keyboard()->is(KEY_A) && this->position().x >= -45.0f)
	{
		position.x -= this->m_speed * this->delta_time();
	}

	if (this->input()->keyboard()->is(KEY_D) && this->position().x <= 45.0f)
	{
		position.x += this->m_speed * this->delta_time();
	}

	if (this->input()->keyboard()->is_pressed(KEY_SPACE) || this->input()->mouse()->is_pressed(MOUSE_LEFT))
	{
		this->m_sound->play();
	}

	if (this->input()->controllers_connected())
	{
		std::shared_ptr<Controller> controller{ this->input()->controller() };

		if (controller->left_analogue_in_motion())
		{
			position.x += controller->left_analogue_x() * this->m_speed * this->delta_time();
			position.y += controller->left_analogue_y() * this->m_speed * this->delta_time();
		}

		if (controller->is_pressed(CONTROLLER_BUTTON_A))
		{
			this->m_sound->play();
		}
	}

	this->transform()->move(position);
}