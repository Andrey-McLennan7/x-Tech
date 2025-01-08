#include "ModelRenderer.h"

#include "Model.h"
#include "Shader.h"
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

		this->m_shader->set_mat4("u_Model", this->transform()->model_matrix());

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