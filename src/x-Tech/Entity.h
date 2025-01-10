#pragma once

#ifndef X_TECH_ENTITY_H
#define X_TECH_ENTITY_H

#include <glm/glm.hpp>

#include <memory>
#include <vector>
#include <stdexcept>

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

		std::vector<std::shared_ptr<Component>> m_components;

		std::weak_ptr<Core> m_core;
		std::weak_ptr<Entity> m_self;
		std::weak_ptr<Transform> m_transform;

		std::string m_name;

		bool m_alive;

	// Private member functions
	private:

		void fixed_tick();
		void tick();
		void late_tick();

		void display();

		void gui();

	// Public member functions
	public:

		~Entity() {};

		template <typename T>
		std::shared_ptr<T> add_component();

		template <typename T>
		std::shared_ptr<T> get_component();

		void kill();

		std::shared_ptr<Transform> transform();
		std::shared_ptr<Core> core();

		// Setter/Getters
		void position(const glm::vec3& position);
		glm::vec3 position() const;

		void rotation(const glm::vec3& rotation);
		glm::vec3 rotation() const;

		void scale(const glm::vec3& scale);
		glm::vec3 scale() const;

		void name(const std::string& name);
		std::string name() const;

		friend class Core;
		friend class Window;
	};
}

#include "Component.h"
#include "Camera.h"
#include "PointLight.h"

#include <iostream>

namespace xTech
{
	template <typename T>
	std::shared_ptr<T> Entity::add_component()
	{
		std::shared_ptr<T> rtn{ std::make_shared<T>() };

		if (typeid(T) == typeid(Camera))
		{
			std::cout << "Camera added" << std::endl;
		}

		rtn->m_entity = this->m_self;

		rtn->on_initialize();
		this->m_components.push_back(rtn);

		return rtn;
	}

	template <typename T>
	std::shared_ptr<T> Entity::get_component()
	{
		std::vector<std::shared_ptr<Component>>::iterator itr;
		for (itr = this->m_components.begin(); itr != this->m_components.end(); ++itr)
		{
			std::shared_ptr<T> rtn = std::dynamic_pointer_cast<T>(*itr);

			if (rtn)
			{
				return rtn;
			}
		}

		throw std::runtime_error("ERROR::FAILED TO FIND COMPONENT");
	}
}

#endif