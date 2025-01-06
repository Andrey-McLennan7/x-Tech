#pragma once

#ifndef REND_CUBE_H
#define REND_CUBE_H

#include "Shape.h"

namespace rend
{
	class Cube : public Shape
	{
	// Public member functions
	public:

		Cube();

		virtual void draw(std::shared_ptr<Shader> shader) override;
	};
}

#endif