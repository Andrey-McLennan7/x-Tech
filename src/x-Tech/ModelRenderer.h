#pragma once

#ifndef X_TECH_MODEL_RENDERER_H
#define X_TECH_MODEL_RENDERER_H

#include "Component.h"

namespace xTech
{
	class Shader;
	class Model;
	class PointLight;

	class ModelRenderer : public Component
	{
	// Private data members
	private:

		std::shared_ptr<Shader> m_shader;
		std::shared_ptr<Model> m_model;

		bool m_attenuation;

	// Public member functions
	public:

		virtual void on_initialize() override;
		virtual void on_display() override;

		void shader(const std::string& path);
		void shader(std::shared_ptr<Shader> shader);

		void model(const std::string& path);
		void model(std::shared_ptr<Model> model);

		void attenuation(bool attenuation);
		bool attenuation() const;
	};
}

#endif