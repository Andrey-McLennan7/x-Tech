#pragma once

#ifndef REND_QUAD_H
#define REND_QUAD_H

#include "Shape.h"

namespace rend
{
	class Quad : public Shape
	{
	// Public member functions
	public:

		Quad();

		virtual void draw(std::shared_ptr<Shader> shader) override;
	};
}

#endif