#pragma once

#ifndef X_TECH_MODEL_RENDERER_H
#define X_TECH_MODEL_RENDERER_H

#include <x-Tech/Component.h>
#include <rend/rend.h>

namespace xTech
{
	class Shader;
	class Model;

	class ModelRenderer : public Component
	{
	// Private data members
	private:

		std::shared_ptr<rend::Shader> m_shader;
		std::shared_ptr<rend::Model> m_model;

	// Public member functions
	public:

		virtual void on_display() override;

		void shader(std::shared_ptr<rend::Shader> shader);
	};
}

#endif