#pragma once

#ifndef REND_FONT_H
#define REND_FONT_H

#include <GL/glew.h>
#include "glm/glm.hpp"

#include <string>
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

		std::map<char, Character> m_characters;

		std::string m_error;
		bool m_success;

	public:

		Font(std::string path);

		void draw(GLuint vao, GLuint vbo, Shader* shader, const std::string& text, glm::vec2 position = glm::vec2(0.0f), float scale = 1.0f);
	};
}

#endif