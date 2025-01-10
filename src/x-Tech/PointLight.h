#pragma once

#ifndef X_TECH_POINT_LIGHT_H
#define X_TECH_POINT_LIGHT_H

#include "Component.h"

namespace xTech
{
	class PointLight : public Component
	{
	// Pirvate data members
	private:

		// Light Options
		glm::vec3 m_direction;
		glm::vec3 m_ambient;
		glm::vec3 m_diffuse;
		glm::vec3 m_specular;

	// Public member functions
	public:

		virtual void on_initialize() override;

		void direction(const glm::vec3& direction);
		glm::vec3 direction() const;

		void ambient(const glm::vec3& ambient);
		glm::vec3 ambient() const;

		void diffuse(const glm::vec3& diffuse);
		glm::vec3 diffuse() const;

		void specular(const glm::vec3& specular);
		glm::vec3 specular() const;
	};
}

#endif