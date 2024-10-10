#include "Core.h"
#include "Entity.h"
#include <iostream>

namespace xTech
{
	std::shared_ptr<Core> Core::initialize()
	{
		std::shared_ptr<Core> rtn = std::make_shared<Core>();
		rtn->m_self = rtn;

		return rtn;
	}

	void Core::run()
	{
		for (int i{ 0 }; i < 5; ++i)
		{
			// TODO
		}

		std::cout << this->m_self.lock().get() << std::endl;
	}

	void Core::end()
	{

	}

	std::shared_ptr<Entity> Core::add_entity()
	{
		std::shared_ptr<Entity> rtn = std::make_shared<Entity>();

		rtn->m_core = this->m_self;
		this->m_entities.push_back(rtn);

		return rtn;
	}
}