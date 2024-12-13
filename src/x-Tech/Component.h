#pragma once

#ifndef X_TECH_COMPONENT_H
#define X_TECH_COMPONENT_H

#include <memory>

namespace xTech
{
	class Entity;
	class Transform;
	class Core;
	class Window;
	class Cache;
	class Input;

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
		void gui();
		void kill();

	// Protected member functions
	protected:

		virtual void on_initialize();

		virtual void on_fixed_tick();
		virtual void on_tick();
		virtual void on_late_tick();

		virtual void on_display();

		virtual void on_gui();

	// Public member functions
	public:

		std::shared_ptr<Entity> entity()	   const;
		std::shared_ptr<Transform> transform() const;
		std::shared_ptr<Core> core()		   const;
		std::shared_ptr<Window> window()	   const;
		std::shared_ptr<Cache> cache()		   const;
		std::shared_ptr<Input> input()		   const;

		float delta_time() const;

		friend Entity;
	};
}

#endif