#pragma once

#ifndef REND_PYRAMID_H
#define REND_PYRAMID_H

#include "Shape.h"

namespace rend
{
	class Pyramid : public Shape
	{
		// Public member functions
	public:

		Pyramid();

		virtual void draw(std::shared_ptr<Shader> shader) override;
	};
}

#endif