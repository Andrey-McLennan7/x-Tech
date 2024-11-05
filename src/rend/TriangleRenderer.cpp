#include "TriangleRenderer.h"

#include "Shader.h"

#include <x-Tech/Transform.h>
#include <x-Tech/Window.h>
#include <x-Tech/Entity.h>

#include <glm/gtc/matrix_transform.hpp>

namespace rend
{
	void TriangleRenderer::on_initialize()
	{
		float vertices[]
		{
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,

			-0.5f,  0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f
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

		this->m_shader = std::make_shared<Shader>("../res/Shaders/vertexShader.glsl", "../res/Shaders/fragmentShader.glsl");
	}

	void TriangleRenderer::on_tick()
	{
		glm::mat4 model{ glm::mat4(1.0f) };
		glm::mat4 projection{ glm::mat4(1.0f) };
		glm::mat4 view{ glm::mat4(1.0f) };

		glm::ivec2 wsize{ this->window()->size() };

		model = this->entity()->get_component<xTech::Transform>()->model();
		this->m_shader->set_mat4("u_Model", model);

		projection = glm::perspective(45.0f, float(wsize.x) / float(wsize.y), 0.1f, 100.0f);
		this->m_shader->set_mat4("u_Projection", projection);

		view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
		this->m_shader->set_mat4("u_View", view);

		this->m_shader->set_vec3("u_Colour", glm::vec3(1.0f, 0.0f, 0.0f));
	}

	void TriangleRenderer::on_display()
	{
		this->m_shader->use();

		glBindVertexArray(this->m_vao);
		glDrawArrays(GL_TRIANGLES, 0, this->m_size);
		glBindVertexArray(0);

		this->m_shader->unuse();
	}
}