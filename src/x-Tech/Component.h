#include <memory>

#ifndef X_TECH_COMPNENT_H
#define X_TECH_COMPNENT_H

namespace xTech
{
	class Entity;

	class Component
	{
	// Private data members
	private:

		std::weak_ptr<Entity> m_entity;

		bool m_alive;

	// Private member functions
	private:

		void tick();
		void display();

		void kill();

	// Public member functions
	public:

		virtual void on_initialize();
		virtual void on_tick();
		virtual void on_display();

		std::shared_ptr<Entity> get_entity();

		friend Entity;
	};
}

#endif