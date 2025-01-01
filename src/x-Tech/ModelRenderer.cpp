#include "ModelRenderer.h"

#include "Model.h"
#include "Shader.h"

namespace xTech
{
	void ModelRenderer::on_display()
	{

	}

	void ModelRenderer::shader(std::shared_ptr<rend::Shader> shader)
	{
		this->m_shader = shader;
	}
}