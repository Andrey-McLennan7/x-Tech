#pragma once

#ifndef REND_FONT_H
#define REND_FONT_H

#include <GL/glew.h>
#include "glm/glm.hpp"

#include <string>
#include <memory>
#include <map>

namespace rend
{
	struct Character
	{
		GLuint textureID;
		GLuint advance;

		glm::ivec2 size;
		glm::ivec2 bearing;
	};

	class GUI;
	class Shader;

	class Font
	{
	private:

		GLuint m_vao;
		GLuint m_vbo;

		std::map<char, Character> m_characters;

	public:

		Font(const std::string& path);

		void draw(std::shared_ptr<Shader> shader, const std::string& text, glm::vec2 position = glm::vec2(0.0f), float scale = 1.0f);
	};
}

#endif