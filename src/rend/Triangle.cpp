#include "Triangle.h"
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stdexcept>

namespace rend
{
	Triangle::Triangle() : Shape()
	{
		float vertices[]
		{
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f,
		};

		this->m_size = (sizeof(vertices) / sizeof(vertices[0])) / 3;

		GLuint vbo{ 0 };

		glGenBuffers(1, &vbo);
		glGenVertexArrays(1, &this->m_vao);

		glBindVertexArray(this->m_vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
	}

	void Triangle::draw(std::shared_ptr<Shader> shader)
	{
		Shape::draw(shader);
	}
}