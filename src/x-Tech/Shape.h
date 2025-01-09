#pragma once

#ifndef X_TECH_SHAPE_H
#define X_TECH_SHAPE_H

#include "Resource.h"
#include <rend/rend.h>

#include <memory>

namespace xTech
{
	class Shader;
	class ShapeRenderer;

	class Shape : public Resource
	{
	// Private data members
	private:

		std::shared_ptr<rend::Shape> m_shape;

	// Public member functions
	public:

		virtual void on_load() override;

		friend class ShapeRenderer;
	};
}

#endif