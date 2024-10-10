#include <memory>

#ifndef X_TECH_COMPNENT_H
#define X_TECH_COMPNENT_H

namespace xTech
{
	class Entity;

	class Component
	{
	public:

		void initialize();

		virtual void onTick();
		virtual void onDisplay();

	private:

		std::weak_ptr<Entity> m_entity;

		bool m_alive;

		void tick();
		void display();

		void kill();

	public:

		friend Entity;
	};
}

#endif