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
		std::shared_ptr<Window> m_window; ///< An instance of the window connected to core
		std::shared_ptr<Input> m_input;   ///< An instance of the input connected to core
		std::shared_ptr<Cache> m_cache;   ///< An instance of the cache connected to core

		// Scene entities
		std::vector<std::shared_ptr<Entity>> m_entities; ///< List of instances of entity connected to core

		// Cameras
		std::weak_ptr<Camera> m_current_camera;		  ///< Pointer to the currently used camera in display
		std::vector<std::weak_ptr<Camera>> m_cameras; ///< List of instances of entity that have a camera component attached to them

		// Lights
		std::weak_ptr<PointLight> m_current_light;		 ///< Pointer to the currently used light source in display
		std::vector<std::weak_ptr<PointLight>> m_lights; ///< List of instances of entity that have a light component attahced to them

		// Additional members
		std::weak_ptr<Core> m_self; ///< Self-referece of core
		bool m_run;					///< Controls the game loop

	// Private member functions
	private:

		/**
		* \brief A seperated instance of the game engine loop
		* 
		* Due to the restrictions of web browsers, we were unable to
		* have a tight loop
		* 
		* \param _core The context of our engine as user data
		* \return The error code
		*/
		static void loop(void* _core);

		/**
		* \brief Identifies user input connected to core
		*
		* Propagates through every type of input and apply changes
		* accordingly
		* 
		*/
		void do_input();

		/**
		* \brief Propagates through every entity and sub-system connected to core
		*
		* Looks through every entity and sub-systems in core and applies changes
		* based on time-lapses and/or user inputs
		*
		*/
		void do_tick();

		/**
		* \brief Propagates through every entity and displays them in window
		*
		* Looks through every entity in core and displays their visual representation
		* in the window connected to core
		*
		*/
		void do_render();

		/**
		* \brief Returns the SDL id of a controller
		* 
		* Provides a robust and safer method of identifying which 
		* controller is being used
		*
		* \param controller_id The internal SDL id
		* \return Array index
		*/
		int controller_index(int controller_id);

	// Public member functions
	public:

		/**
		* \brief Initializes core
		* 
		* Is static to prevent components from calling it and to
		* return a shared pointer of it
		* 
		* \return Shared pointer to core
		*/
		static std::shared_ptr<Core> initialize();

		/**
		* \brief Creates an entity and connnects it core
		* 
		* \return Shared pointer to entity
		*/
		std::shared_ptr<Entity> add_entity();

		/**
		* \brief Returns an existing entity connected to core by their name
		* 
		* Will throw a runtime error if no entity with such name exists
		* 
		* \param name The name of the entity
		* \return Shared pointer to entity
		*/
		std::shared_ptr<Entity> get_entity_by_name(const std::string& name) const;

		/**
		* \brief Returns an existing entity connected to core by their tag
		*
		* Will throw a runtime error if no entity with such tag exists
		*
		* \param tag The tag of the entity
		* \return Shared pointer to entity
		*/
		std::shared_ptr<Entity> get_entity_by_tag(const std::string& tag) const;

		/**
		* \brief Returns the currently used camera
		*
		* \return Shared pointer to camera component attached to an entity
		*/
		std::shared_ptr<Camera> current_camera() const;

		/**
		* \brief Returns the currently used light source
		*
		* \return Shared pointer to light source component attached to an entity
		*/
		std::shared_ptr<PointLight> current_light() const;

		/**
		* \brief Initiates game loop when called
		* 
		*/
		void run();

		/**
		* \brief Ends game loop when called
		*
		*/
		void end();

		/**
		* \brief Returns reference to window
		*
		* \return Shared pointer to window
		*/
		std::shared_ptr<Window> window() const;

		/**
		* \brief Returns reference to cache
		*
		* \return Shared pointer to cache
		*/
		std::shared_ptr<Cache> cache() const;

		/**
		* \brief Returns reference to input
		*
		* \return Shared pointer to input
		*/
		std::shared_ptr<Input> input() const;

		/**
		* \brief Returns reference to camera
		*
		* If no argument is provided - defaults to first camera in the scene
		* If argument is less than 0 - defaults to first camera in the scene
		* If argument is gearter than total amount of camera - defaults to last camera in the scene
		* Throws runtime error if no cameras are found in the scene
		* 
		* \param index The index towards a specific camera
		* \return Shared pointer to camera
		*/
		std::shared_ptr<Camera> camera(int index = 0) const;

		/**
		* \brief Returns reference to light sourcee
		*
		* If no argument is provided - defaults to first light source in the scene
		* If argument is less than 0 - defaults to first light source in the scene
		* If argument is gearter than total amount of camera - defaults to last light source in the scene
		* Throws runtime_error if no light sources are found in the scene
		*
		* \param index The index towards a specific light source
		* \return Shared pointer to light source
		*/
		std::shared_ptr<PointLight> light(int index = 0) const;

		/**
		* \brief Returns list of attached user-specified components to entities
		* 
		* \param out A vector shared pointers to components attached to entities
		*/
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