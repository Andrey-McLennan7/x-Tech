#pragma once

#ifndef X_TECH_COMPONENT_H
#define X_TECH_COMPONENT_H

#include <glm/glm.hpp>

#include <memory>
#include <string>

namespace xTech
{
	class Entity;
	class Transform;
	class Core;
	class Window;
	class Cache;
	class Input;
	class Camera;

	class Component
	{
	// Private data members
	private:

		std::weak_ptr<Entity> m_entity;

		bool m_alive;

	// Private member functions
	private:

		/**
		* \brief Calls component function on_fixed_tick()
		* 
		*/
		void fixed_tick();

		/**
		* \brief Calls component function on_tick()
		*
		*/
		void tick();

		/**
		* \brief Calls component function on_late_tick()
		*
		*/
		void late_tick();

		/**
		* \brief Calls component function on_display()
		*
		*/
		void display();

		/**
		* \brief Calls component function on_gui()
		*
		*/
		void gui();

		/**
		* \brief Deletes component from entity
		*
		*/
		void kill();

	// Protected member functions
	protected:

		/**
		* \brief Called once
		* 
		* Is the first function executed when component is attached to entity
		* 
		*/
		virtual void on_initialize();

		/**
		* \brief Called every 0.02 seconds (20 milliseconds)
		*
		* Is executed every 50 frames per second
		*
		*/
		virtual void on_fixed_tick();

		/**
		* \brief Called every frame
		*
		* Is executed every frame per second (e.g., 60 FPS - 60 times per second,
		* 30 FPS - 30 times per second)
		*
		*/
		virtual void on_tick();

		/**
		* \brief Called last every frame
		*
		* Is the last tick to execute every frame per second (e.g., 60 FPS - 60 times
		* per second, 30 FPS - 30 times per second)
		*
		*/
		virtual void on_late_tick();

		/**
		* \brief Called every frame
		*
		* Displays every visual representations of the component
		*
		*/
		virtual void on_display();

		/**
		* \brief Called every frame
		*
		* Is called for rendering and handling GUI events
		*
		*/
		virtual void on_gui();

	// Public member functions
	public:

		/**
		* \brief Returns reference to component's parent entity
		* 
		* \return Shared pointer of component's parent entity
		*/
		std::shared_ptr<Entity> entity() const;

		/**
		* \brief Return reference to component's parent entity transform component
		*
		* \return Shared pointer of component's parent entity transform component
		*/
		std::shared_ptr<Transform> transform() const;

		/**
		* \brief Returns reference to core
		*
		* \return Shared pointer to core
		*/
		std::shared_ptr<Core> core() const;

		/**
		* \brief Returns reference to window sub-engine connected to core
		*
		* \return Shared pointer to window
		*/
		std::shared_ptr<Window> window() const;

		/**
		* \brief Returns reference to cache sub-engine connected to core
		*
		* \return Shared pointer to cache
		*/
		std::shared_ptr<Cache> cache() const;

		/**
		* \brief Returns reference to input sub-engine connected to core
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
		* \brief Set position of component's parent entity
		*
		* \param position A glm::vec3 parameter
		*/
		void position(const glm::vec3& position);

		/**
		* \brief Set position of component's parent entity
		*
		* \param x, y, z Three float parameters
		*/
		void position(float x, float y, float z);

		/**
		* \brief Returns position of component's parent entity
		*
		* \return Position of entity
		*/
		glm::vec3 position() const;

		/**
		* \brief Set rotation of component's parent entity
		*
		* \param position A glm::vec3 parameter
		*/
		void rotation(const glm::vec3& rotation);

		/**
		* \brief Set rotation of component's parent entity
		*
		* \param x, y, z Three float parameters
		*/
		void rotation(float x, float y, float z);

		/**
		* \brief Returns rotation of component's parent entity
		*
		* \return Rotation of entity
		*/
		glm::vec3 rotation() const;

		/**
		* \brief Set scale of component's parent entity
		*
		* \param scale A glm::vec3 parameter
		*/
		void scale(const glm::vec3& scale);

		/**
		* \brief Set scale of component's parent entity
		*
		* \param x, y, z Three float parameters
		*/
		void scale(float x, float y, float z);

		/**
		* \brief Set scale of component's parent entity
		*
		* \param scale A float parameter
		*/
		void scale(float scale);

		/**
		* \brief Returns scale of component's parent entity
		*
		* \return Scale of entity
		*/
		glm::vec3 scale() const;

		/**
		* \brief Locks the component's parent entity scale to a shared value
		*
		* \param lock A boolean parameter
		*/
		void lock_scale(bool lock);

		/**
		* \brief Sets the name of the component's parent entity
		*
		* \param name A std::string parameter
		*/
		void name(const std::string& name);

		/**
		* \brief Returns the name of the component's parent entity
		*
		* \return The name of the entity
		*/
		std::string name() const;
		
		/**
		* \brief Sets tag of the component's parent entity
		*
		* \param tag A std::string parameter
		*/
		void tag(const std::string& tag);

		/**
		* \brief Returns the component's parent entity tag
		*
		* \return The entity tag
		*/
		std::string tag() const;

		/**
		* \brief Return the delta time from the window sub-engine connected to core
		*
		* \return Delta time
		*/
		float delta_time() const;

		friend class Entity;
	};
}

#endif