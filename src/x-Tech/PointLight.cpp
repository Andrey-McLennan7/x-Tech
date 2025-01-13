#include "PointLight.h"

#include "Core.h"

namespace xTech
{
	void PointLight::on_initialize()
	{
		this->m_direction = glm::normalize(this->position());
		this->m_ambient = glm::vec3{ 0.8f };
		this->m_diffuse = glm::vec3{ 0.4f };
		this->m_specular = glm::vec3{ 0.5f };

		this->core()->m_lights.push_back(this->entity()->get_component<PointLight>());
	}

	void PointLight::direction(const glm::vec3& direction)
	{
		this->m_direction = glm::normalize(direction);
	}

	glm::vec3 PointLight::direction() const
	{
		return glm::normalize(this->m_direction);
	}

	void PointLight::ambient(const glm::vec3& ambient)
	{
		this->m_ambient = ambient;
	}

	glm::vec3 PointLight::ambient() const
	{
		return this->m_ambient;
	}

	void PointLight::diffuse(const glm::vec3& diffuse)
	{
		this->m_diffuse = diffuse;
	}

	glm::vec3 PointLight::diffuse() const
	{
		return this->m_diffuse;
	}

	void PointLight::specular(const glm::vec3& specular)
	{
		this->m_specular = specular;
	}

	glm::vec3 PointLight::specular() const
	{
		return this->m_specular;
	}
}