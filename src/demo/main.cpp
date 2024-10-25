#include <x-Tech/x-Tech.h>
#include <glm/gtc/matrix_transform.hpp>

using namespace xTech;

class TriangleRenderer : public Component
{
private:

	GLuint m_vao;
	int m_size;

	std::shared_ptr<Shader> m_shader;

public:

	virtual void on_initialize() override
	{
		float vertices[]
		{
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f,
		};

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

		this->m_shader = std::make_shared<Shader>("res/Shaders/vertexShader.glsl", "res/Shaders/fragmentShader.glsl");
	}

	virtual void on_tick() override
	{

	}

	virtual void on_display() override
	{
		mat4 model{ mat4(1.0f) };
		mat4 projection{ mat4(1.0f) };
		mat4 view{ mat4(1.0f) };

		int width{ this->get_entity()->get_core()->get_window()->get_width() };
		int height{ this->get_entity()->get_core()->get_window()->get_height() };

		model = this->get_entity()->get_component<Transform>()->m_model_matrix;
		this->m_shader->set_mat4("model", model);

		projection = glm::perspective(45.0f, float(width) / float(height), 0.1f, 100.0f);
		this->m_shader->set_mat4("projection", projection);

		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -1.0f));
		this->m_shader->set_mat4("view", view);

		this->m_shader->set_vec3("uColour", glm::vec3(1.0f, 0.0f, 0.0f));



		this->m_shader->use();

		glBindVertexArray(this->m_vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		this->m_shader->unuse();
	}

};

#undef main
int main()
{
	std::shared_ptr<Core> core{ Core::initialize() };

	std::shared_ptr<Entity> entity{ core->add_entity() };
	std::shared_ptr<TriangleRenderer> triangle{ entity->add_component<TriangleRenderer>() };

	core->run();

	return 0;
}