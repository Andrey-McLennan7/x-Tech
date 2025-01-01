#pragma once

#ifndef X_TECH_MODEL_H
#define X_TECH_MODEL_H

#include "Resource.h"
#include <rend/rend.h>

#include <memory>

namespace xTech
{
	class Shader;

	class Model : public Resource
	{
	// Private data members
	private:

		std::shared_ptr<rend::Model> m_model;

	// Public member functions
	public:

		virtual void on_load() override;
		void draw(std::shared_ptr<Shader> shader);
	};

}

#endif