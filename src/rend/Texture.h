#pragma once

#ifndef REND_TEXTURE_H
#define REND_TEXTURE_H

#include <x-Tech/Resource.h>

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>

namespace rend
{
	class Texture
	{
	// Private data members
	private:

		std::vector<float> m_data;

		int m_width;
		int m_height;

		bool m_dirty;
		GLuint m_id;

	// Public member functions
	public:

		Texture();
		Texture(const Texture& copy);

		Texture& operator=(const Texture& assign);

		~Texture();

		Texture(const std::string& _path);
		Texture(int _width, int _height);

		void load(const std::string& _path);
		void load(const std::vector<unsigned char>& data);

		int width() const;
		void width(int width);

		int height() const;
		void height(int height);

		void size(int width, int height);
		glm::vec2 size() const;

		glm::vec4 pixel(int x, int y) const;
		void pixel(int x, int y, glm::vec4 pixel);

		GLuint ID();
	};

}

#endif