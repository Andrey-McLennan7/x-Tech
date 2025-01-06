#pragma once

#ifndef X_TECH_SHAPE_H
#define X_TECH_SHAPE_H

#include "Resource.h"
#include <rend/rend.h>

#include <memory>

namespace xTech
{
	class Shader;

	class Shape : public Resource
	{
	// Private data members
	private:

		std::shared_ptr<rend::Shape> m_shape;

	// Public member functions
	public:

		virtual void on_load() override;
		void draw(std::shared_ptr<Shader> shader);
	};
}

#endif