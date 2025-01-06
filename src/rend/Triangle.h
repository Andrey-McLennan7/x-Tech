#pragma once

#ifndef REND_TRIANGLE_H
#define REND_TRIANGLE_H

#include "Shape.h"

namespace rend
{
	class Triangle : public Shape
	{
	// Public member functions
	public:

		Triangle();

		virtual void draw(std::shared_ptr<Shader> shader) override;
	};
}

#endif