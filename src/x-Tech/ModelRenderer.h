#pragma once

#ifndef X_TECH_MODEL_RENDERER_H
#define X_TECH_MODEL_RENDERER_H

#include "Component.h"

namespace xTech
{
	class Shader;
	class Model;

	class ModelRenderer : public Component
	{
	// Private data members
	private:

		std::shared_ptr<Shader> m_shader;
		std::shared_ptr<Model> m_model;

	// Public member functions
	public:

		virtual void on_display() override;

		void shader(std::shared_ptr<Shader> shader);
		void model(std::shared_ptr<Model> model);
	};
}

#endif