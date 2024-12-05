#include <memory>

#ifndef X_TECH_COMPNENT_H
#define X_TECH_COMPNENT_H

namespace xTech
{
	class Entity;
	class Transform;
	class Core;
	class Window;
	class Cache;

	class Component
	{
	// Private data members
	private:

		std::weak_ptr<Entity> m_entity;

		bool m_alive;

	// Private member functions
	private:

		void fixed_tick();
		void tick();
		void late_tick();

		void display();
		void kill();

	// Protected member functions
	protected:

		virtual void on_initialize();

		virtual void on_fixed_tick();
		virtual void on_tick();
		virtual void on_late_tick();

		virtual void on_display();

	// Public member functions
	public:

		std::shared_ptr<Entity> entity()	   const;
		std::shared_ptr<Transform> transform() const;
		std::shared_ptr<Core> core()		   const;
		std::shared_ptr<Window> window()	   const;
		std::shared_ptr<Cache> cache()		   const;

		friend Entity;
	};
}

#endif