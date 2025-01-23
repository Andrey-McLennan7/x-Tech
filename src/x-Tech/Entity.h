#pragma once

#ifndef X_TECH_ENTITY_H
#define X_TECH_ENTITY_H

#include <glm/glm.hpp>

#include <string>
#include <memory>
#include <vector>

namespace xTech
{
	class Core;
	class Window;
	class Transform;
	class Component;

	class Entity
	{
	// Private data members
	private:

		std::vector<std::shared_ptr<Component>> m_components; ///< List of instances of component connected to entity

		std::weak_ptr<Core> m_core;			  ///< Referece to core
		std::weak_ptr<Entity> m_self;		  ///< Self-referece of entity
		std::weak_ptr<Transform> m_transform; ///< Referece to entity transform

		std::string m_name; ///< Name of entity
		std::string m_tag;  ///< Entity tag

		bool m_alive;

	// Private member functions
	private:

		/**
		* \brief Loops through each component fixed tick function connected to entity
		*
		* Executes every 0.02 seconds (20 ms) or 50 times per secons, used for physics calculations
		*
		*/
		void fixed_tick();

		/**
		* \brief Loops through each component tick function connected to entity
		*
		* Executes every frame per second
		*
		*/
		void tick();

		/**
		* \brief Loops through each component late tick function connected to entity
		*
		* Executes every frame per second last
		*
		*/
		void late_tick();

		/**
		* \brief Loops through each component display function connected to entity
		*
		*/
		void display();

		/**
		* \brief Loops through each component gui function connected to entity
		*
		*/
		void gui();

		template <typename T>
		void remove_sub_str(std::basic_string<T>& s, const std::basic_string<T> p);

	// Public member functions
	public:

		Entity();

		/**
		* \brief Creates and attaches component to entity
		*
		* \return Shared pointer to component
		*/
		template <typename T>
		std::shared_ptr<T> add_component();

		/**
		* \brief Returns user-specified component attached to entity
		*
		* Throws a runtime error if no such component is attached to entity
		* 
		* \return Shared pointer to component
		*/
		template <typename T>
		std::shared_ptr<T> get_component();

		/**
		* \brief Deletes entity from core
		*
		*/
		void kill();

		/**
		* \brief Returns reference to transform component
		*
		* \return Shared pointer to transform
		*/
		std::shared_ptr<Transform> transform();

		/**
		* \brief Returns reference to core
		*
		* \return Shared pointer to core
		*/
		std::shared_ptr<Core> core();

		/**
		* \brief Set position of entity
		*
		* \param position A glm::vec3 parameter
		*/
		void position(const glm::vec3& position);

		/**
		* \brief Set position of entity
		*
		* \param x, y, z Three float parameters
		*/
		void position(float x, float y, float z);

		/**
		* \brief Returns position of entity
		*
		* \return Position of entity
		*/
		glm::vec3 position() const;

		/**
		* \brief Set rotation of entity
		*
		* \param position A glm::vec3 parameter
		*/
		void rotation(const glm::vec3& rotation);
		
		/**
		* \brief Set rotation of entity
		*
		* \param x, y, z Three float parameters
		*/
		void rotation(float x, float y, float z);

		/**
		* \brief Returns rotation of entity
		*
		* \return Rotation of entity
		*/
		glm::vec3 rotation() const;

		/**
		* \brief Set scale of entity
		*
		* \param scale A glm::vec3 parameter
		*/
		void scale(const glm::vec3& scale);
		
		/**
		* \brief Set scale of entity
		*
		* \param x, y, z Three float parameters
		*/
		void scale(float x, float y, float z);

		/**
		* \brief Set scale of entity
		*
		* \param scale A float parameter
		*/
		void scale(float scale);

		/**
		* \brief Returns scale of entity
		*
		* \return Scale of entity
		*/
		glm::vec3 scale() const;

		/**
		* \brief Locks entity's scale to a shared value
		*
		* \param lock A boolean parameter
		*/
		void lock_scale(bool lock);

		/**
		* \brief Sets the name of the entity
		*
		* \param name A std::string parameter
		*/
		void name(const std::string& name);

		/**
		* \brief Returns the name of the entity
		*
		* \return The name of the entity
		*/
		std::string name() const;

		/**
		* \brief Sets tag of the entity
		*
		* \param tag A std::string parameter
		*/
		void tag(const std::string& tag);

		/**
		* \brief Returns the entity tag
		*
		* \return The entity tag
		*/
		std::string tag() const;

		friend class Core;
		friend class Window;
	};
}

#include "Component.h"
#include <stdexcept>

namespace xTech
{
	template <typename T>
	void Entity::remove_sub_str(std::basic_string<T>& s, const std::basic_string<T> p)
	{
		std::basic_string<T>::size_type n{ p.length() };

		for (std::basic_string<T>::size_type i{ s.find(p) };
			i != std::basic_string<T>::npos; i = s.find(p))
		{
			s.erase(i, n);
		}
	}

	template <typename T>
	std::shared_ptr<T> Entity::add_component()
	{
		std::shared_ptr<T> rtn{ std::make_shared<T>() };

		rtn->m_entity = this->m_self;
		rtn->m_alive = true;

		this->m_components.push_back(rtn);
		rtn->on_initialize();

		return rtn;
	}

	template <typename T>
	std::shared_ptr<T> Entity::get_component()
	{
		std::vector<std::shared_ptr<Component>>::iterator itr;
		for (itr = this->m_components.begin(); itr != this->m_components.end(); ++itr)
		{
			std::shared_ptr<T> rtn{ std::dynamic_pointer_cast<T>(*itr) };

			if (rtn)
			{
				return rtn;
			}
		}

		throw std::runtime_error("ERROR::FAILED TO FIND COMPONENT");
	}
}

#endif