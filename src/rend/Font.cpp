#include "Font.h"
#include "Shader.h"

#include <stdexcept>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace rend
{
	Font::Font(const std::string& path)
	{
		FT_Library ft;

		if (FT_Init_FreeType(&ft))
		{
			throw std::runtime_error("ERROR::FAILED TO INITIALISE FREETPE");
		}

		FT_Face face;
		if (FT_New_Face(ft, path.c_str(), 0, &face))
		{
			throw std::runtime_error("ERROR::FAILED TO LOAD FONT");
		}

		FT_Set_Pixel_Sizes(face, 0, 48);

		// Disable byte-alignment restriction
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		for (GLubyte c{ 0 }; c < 128; ++c)
		{
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				continue;
			}

			// Generate texture
			GLuint texture;
			glGenTextures(1, &texture);

			glBindTexture(GL_TEXTURE_2D, texture);

			glTexImage2D
			(
				GL_TEXTURE_2D, 0, GL_RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0, GL_RED, GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
			);

			// Set Texture Options
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			// Store characters for later use
			Character character =
			{
				texture,
				face->glyph->advance.x,

				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top)
			};

			this->m_characters.insert(std::pair<char, Character>(c, character));
		}

		FT_Done_Face(face);
		FT_Done_FreeType(ft);

		glGenBuffers(1, &this->m_vbo);
		glGenVertexArrays(1, &this->m_vao);

		glBindVertexArray(this->m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, this->m_vbo);

		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void Font::draw(Shader* shader, const std::string& text, glm::vec2 position, float scale)
	{
		shader->use();
		glActiveTexture(GL_TEXTURE0);

		glBindVertexArray(this->m_vao);

		// Iterate through all characters
		for (std::string::const_iterator c = text.begin(); c != text.end(); ++c)
		{
			Character ch = this->m_characters[*c];

			float xpos{ position.x + ch.bearing.x * scale };
			float ypos{ position.y - (ch.size.y - ch.bearing.y) * scale };

			float w{ ch.size.x * scale };
			float h{ ch.size.y * scale };

			float vertices[6][4] =
			{
				{ xpos,     ypos + h, 0.0f, 0.0f },
				{ xpos,     ypos,	  0.0f, 1.0f },
				{ xpos + w, ypos,	  1.0f, 1.0f },

				{ xpos,     ypos + h, 0.0f, 0.0f },
				{ xpos + w, ypos,	  1.0f, 1.0f },
				{ xpos + w, ypos + h, 1.0f, 0.0f }
			};

			// Render glymth texture over quad
			glBindTexture(GL_TEXTURE_2D, ch.textureID);

			// Update content of VBO memory
			glBindBuffer(GL_ARRAY_BUFFER, this->m_vbo);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			// Render Quad
			glDrawArrays(GL_TRIANGLES, 0, 6);

			position.x += (ch.advance >> 6) * scale;
		}

		glBindVertexArray(this->m_vao);
		glBindTexture(GL_TEXTURE_2D, 0);

		shader->unuse();
	}
}