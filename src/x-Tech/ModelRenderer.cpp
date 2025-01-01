#include "ModelRenderer.h"

#include "Model.h"
#include "Shader.h"

namespace xTech
{
	void ModelRenderer::on_display()
	{
		this->m_model->draw(this->m_shader);
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