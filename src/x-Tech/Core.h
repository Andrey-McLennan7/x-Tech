#pragma once

#ifndef X_TECH_CORE_H
#define X_TECH_CORE_H

#include <glm/glm.hpp>

#include <memory>
#include <vector>
#include <string>

namespace xTech
{
	class Window;
	class Camera;
	class Cache;
	class Audio;
	class Entity;
	class Input;
	class ShapeRenderer;
	class ModelRenderer;
	class PointLight;
	class ModelRenderer;

	// Core implementation
	class Core
	{
	// Private data members
	private:

		// Core components
		std::shared_ptr<Window> m_window;
		std::shared_ptr<Input> m_input;
		std::shared_ptr<Cache> m_cache;

		// Scene entities
		std::vector<std::shared_ptr<Entity>> m_entities;

		// Cameras
		std::weak_ptr<Camera> m_current_camera;
		std::vector<std::weak_ptr<Camera>> m_cameras;

		// Lights
		std::weak_ptr<PointLight> m_current_light;
		std::vector<std::weak_ptr<PointLight>> m_lights;

		// Additional members
		std::weak_ptr<Core> m_self;
		bool m_run;

	// Private member functions
	private:

		static void loop(void* _core);

		void do_input();
		void do_tick();
		void do_render();

		int controller_index(int controller_id);

	// Public member functions
	public:

		static std::shared_ptr<Core> initialize();

		std::shared_ptr<Entity> add_entity();
		std::shared_ptr<Entity> get_entity_by_name(const std::string& name) const;
		std::shared_ptr<Entity> get_entity_by_tag(const std::string& tag) const;

		std::shared_ptr<Camera> current_camera() const;
		std::shared_ptr<PointLight> current_light() const;

		void run();
		void end();

		std::shared_ptr<Window> window() const;
		std::shared_ptr<Cache> cache() const;
		std::shared_ptr<Input> input() const;
		std::shared_ptr<Camera> camera(int index = 0) const;
		std::shared_ptr<PointLight> light(int index = 0) const;

		template<typename T>
		void find(std::vector<std::shared_ptr<T>>& out);

		friend class Entity;
		friend class Camera;
		friend class PointLight;
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