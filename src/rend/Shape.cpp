#include "Shape.h"
#include "Shader.h"

namespace rend
{
	Shape::Shape() : m_vao{ 0 }, m_size{ 0 }
	{}

	void Shape::draw(std::shared_ptr<Shader> shader)
	{
		shader->use();

		glBindVertexArray(this->m_vao);
		glDrawArrays(GL_TRIANGLES, 0, this->m_size);
		glBindVertexArray(0);

		shader->unuse();
	}
}