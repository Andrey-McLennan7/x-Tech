#pragma once

#ifndef REND_SHAPE_H
#define REND_SHAPE_H

#include <GL/glew.h>
#include <memory>

namespace rend
{
	class Shader;

	class Shape
	{
	// Private data members
	protected:

		GLuint m_vao;
		int m_size;

	// Public member functions
	public:

		Shape();

		virtual void draw(std::shared_ptr<Shader> shader);
	};
}

#endif