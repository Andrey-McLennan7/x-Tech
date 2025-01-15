#pragma once

#ifndef X_TECH_INPUT_H
#define X_TECH_INPUT_H

#include <vector>
#include <memory>

#include <glm/glm.hpp>

namespace xTech
{
	class Core;

	class Mouse;
	class Keyboard;
	class Controller;

	class Input
	{
	// Private data members
	private:

		std::shared_ptr<Keyboard> m_keyboard;
		std::shared_ptr<Mouse> m_mouse;

		std::vector<std::shared_ptr<Controller>> m_controllers;

	// Public member functions
	public:

		Input();
		~Input();

		std::shared_ptr<Keyboard> keyboard();
		std::shared_ptr<Mouse> mouse();

		std::shared_ptr<Controller> controller(int index = 0);
		int controller_number() const;

		friend class Core;
	};
}

#endif