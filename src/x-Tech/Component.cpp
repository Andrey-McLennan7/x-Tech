#include "Component.h"

namespace xTech
{
	void Component::initialize()
	{

	}

	void Component::onTick() {};
	void Component::onDisplay() {};

	void Component::tick()
	{
		this->onTick();
	}

	void Component::display()
	{
		this->onDisplay();
	}
	void Component::kill()
	{
		m_alive = false;
	}
}