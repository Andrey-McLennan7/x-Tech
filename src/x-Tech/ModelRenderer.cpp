#include "ModelRenderer.h"

#include "Model.h"
#include "Shader.h"

#include <stdexcept>

namespace xTech
{
	void ModelRenderer::on_display()
	{
		if (this->m_shader)
		{
			this->m_model->draw(this->m_shader);
		}
		else
		{
			throw std::runtime_error("ERROR::NO SHADERS ARE FOUND");
		}
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