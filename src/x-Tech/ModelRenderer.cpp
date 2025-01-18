#include "ModelRenderer.h"

#include "Core.h"
#include "Model.h"
#include "Shader.h"
#include "Camera.h"
#include "PointLight.h"
#include "Transform.h"
#include "Cache.h"

#include "glm/gtc/matrix_transform.hpp"

#include <stdexcept>

namespace xTech
{
	void ModelRenderer::on_initialize()
	{
		this->m_attenuation = false;
	}

	void ModelRenderer::on_display()
	{
		if (!this->m_shader)
		{
			throw std::runtime_error("ERROR::NO SHADERS FOUND");
		}

		// Vertex shader
		this->m_shader->set_mat4("u_Projection", this->core()->current_camera()->projection_matrix());
		this->m_shader->set_mat4("u_View", this->core()->current_camera()->view_matrix());
		this->m_shader->set_mat4("u_Model", this->transform()->model_matrix());

		// Fragment shader
		this->m_shader->set_vec3("u_ViewPos", this->core()->current_camera()->position());

		if (this->core()->current_light())
		{
			this->m_shader->set_vec3("u_Light.position", this->core()->current_light()->position());
			this->m_shader->set_vec3("u_Light.direction", this->core()->current_light()->direction());

			this->m_shader->set_vec3("u_Light.ambient", this->core()->current_light()->ambient());
			this->m_shader->set_vec3("u_Light.diffuse", this->core()->current_light()->diffuse());
			this->m_shader->set_vec3("u_Light.specular", this->core()->current_light()->specular());

			this->m_shader->set_bool("u_Attenuation", this->m_attenuation);
		}
		else
		{
			glm::vec3 light_pos{ 0.0f };

			this->m_shader->set_vec3("u_Light.position", light_pos);
			this->m_shader->set_vec3("u_Light.direction", glm::normalize(light_pos));

			this->m_shader->set_vec3("u_Light.ambient", glm::vec3{ 0.8f });
			this->m_shader->set_vec3("u_Light.diffuse", glm::vec3{ 0.4f });
			this->m_shader->set_vec3("u_Light.specular", glm::vec3{ 0.5f });

			this->m_shader->set_bool("u_Attenuation", false);
		}

		this->m_model->m_model->draw(this->m_shader->shader());
	}

	void ModelRenderer::shader(const std::string& path)
	{
		this->shader(this->cache()->load<Shader>(path));
	}

	void ModelRenderer::shader(std::shared_ptr<Shader> shader)
	{
		this->m_shader = shader;
	}

	void ModelRenderer::model(const std::string& path)
	{
		this->model(this->cache()->load<Model>(path));
	}
	
	void ModelRenderer::model(std::shared_ptr<Model> model)
	{
		this->m_model = model;
	}

	void ModelRenderer::attenuation(bool attenuation)
	{
		this->m_attenuation = attenuation;
	}

	bool ModelRenderer::attenuation() const
	{
		return this->m_attenuation;
	}
}