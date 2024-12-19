#pragma once

#ifndef X_TECH_CORE_H
#define X_TECH_CORE_H

#include <memory>
#include <vector>

namespace xTech
{
	class Window;
	class Cache;
	class Audio;
	class Entity;
	class Input;

	// Core implementation
	class Core
	{
		// Private data members
	private:

		std::shared_ptr<Window> m_window;
		std::shared_ptr<Input> m_input;
		std::shared_ptr<Audio> m_audio;
		std::shared_ptr<Cache> m_cache;
		//std::shared_ptr<Physics> m_physics;

		bool m_run;

		std::vector<std::shared_ptr<Entity>> m_entities;
		std::weak_ptr<Core> m_self;

		// Private member functions
	private:

		static void loop(void* _core);

		void do_input();
		void do_tick();
		void do_render();

		// Public member functions
	public:

		static std::shared_ptr<Core> initialize();

		void run();
		void end();

		std::shared_ptr<Entity> add_entity();

		template<typename T>
		void find(std::vector<std::shared_ptr<T>>& out);

		std::shared_ptr<Window> window() const;
		std::shared_ptr<Cache> cache() const;
		std::shared_ptr<Input> input() const;

		friend class Entity;
	};
}

#include "Entity.h"
#include "Component.h"

namespace xTech
{
	template<typename T>
	void Core::find(std::vector<std::shared_ptr<T>>& out)
	{
		// Go through each Entity in the Core
		std::vector<std::shared_ptr<Entity>>::iterator entity;
		for (entity = this->m_entities.begin(); entity != this->m_entities.end(); ++entity)
		{
			// Go through each Component in Entity
			std::vector<std::shared_ptr<Component>>::iterator component;
			for (component = (*entity)->m_components.begin(); component != (*entity)->m_components.end(); ++component)
			{
				// Try to dynamic cast the component to a T
				std::shared_ptr<T> t{ std::dynamic_pointer_cast<T>(*component) };

				// If succeeds then add it to the output array
				if (t)
				{
					out.push_back(t);
				}
			}
		}
	}
}

#endif