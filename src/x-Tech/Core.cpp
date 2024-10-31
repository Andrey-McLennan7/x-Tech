#include "Core.h"
#include "Entity.h"
#include "Debug.h"
#include "Transform.h"

#include <rend/Window.h>
#include <rend/Shader.h>

#include <GL/glew.h>
#include <SDL2/SDL.h>

namespace xTech
{
	std::shared_ptr<Core> Core::initialize()
	{
		std::shared_ptr<Core> rtn = std::make_shared<Core>();

		// Make pointer reference to self
		rtn->m_self = rtn;

		rtn->m_run = true;

		// Create window
		rtn->m_window = std::make_shared<Window>();
		rtn->m_window->m_core = rtn->m_self;

		return rtn;
	}

	void Core::run()
	{
		// Start game loop
		while (this->m_run)
		{
			this->m_window->delta_time();
			this->m_window->input();
			this->m_window->tick();
			this->m_window->display();
		}
	}

	void Core::end()
	{
		this->m_run = false;
	}

	std::shared_ptr<Entity> Core::add_entity()
	{
		std::shared_ptr<Entity> rtn = std::make_shared<Entity>();

		rtn->m_core = this->m_self;
		rtn->m_self = rtn;

		rtn->add_component<Transform>();

		this->m_entities.push_back(rtn);

		return rtn;
	}

	std::shared_ptr<Window> Core::get_window()
	{
		return this->m_window;
	}
}