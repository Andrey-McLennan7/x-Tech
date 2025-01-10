#include "ModelRenderer.h"

#include "Core.h"
#include "Model.h"
#include "Shader.h"
#include "Camera.h"
#include "PointLight.h"
#include "Transform.h"

#include "glm/gtc/matrix_transform.hpp"

#include <stdexcept>

namespace xTech
{
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

		this->m_shader->set_vec3("u_Light.position", this->core()->current_light()->position());
		this->m_shader->set_vec3("u_Light.direction", this->core()->current_light()->direction());

		this->m_shader->set_vec3("u_Light.ambient", this->core()->current_light()->ambient());
		this->m_shader->set_vec3("u_Light.diffuse", this->core()->current_light()->diffuse());
		this->m_shader->set_vec3("u_Light.specular", this->core()->current_light()->specular());

		this->m_model->m_model->draw(m_shader->shader());
	}

	void ModelRenderer::shader(std::shared_ptr<Shader> shader)
	{
		this->m_shader = shader;
	}

	void ModelRenderer::model(std::shared_ptr<Model> model)
	{
		this->m_model = model;
	}
}