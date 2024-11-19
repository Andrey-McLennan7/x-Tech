#include <x-Tech/Component.h>
#include <rend/rend.h>

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace xTech
{
	class Shader;

	class TriangleRenderer : public Component
	{
	private:

		GLuint m_vao;
		int m_size;

		std::shared_ptr<Shader> m_shader;

	public:

		TriangleRenderer() : m_vao{ 0 }, m_size{ 0 } {};

		virtual void on_initialize() override;
		virtual void on_tick() override;
		virtual void on_display() override;

	};
}