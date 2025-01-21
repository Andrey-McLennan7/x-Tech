#pragma once

#ifndef REND_MESH_H
#define REND_MESH_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>
#include <memory>


// Code source: https://learnopengl.com/Model-Loading/Mesh
// Reused from 3DGP Assignment 2

namespace rend
{
	struct vertex
	{
		glm::vec3 Positions;
		glm::vec3 Normals;
		glm::vec2 TexCoords;
	};

	struct texture
	{
		GLuint id;
		std::string type;
		std::string path;
	};

	class Shader;

	class Mesh
	{
	private:

		// Render Data
		GLuint m_vao;
		GLuint m_vbo;
		GLuint m_ebo;

		// Mesh Data
		std::vector<vertex> m_vertices;
		std::vector<GLuint> m_indecies;
		std::vector<texture> m_textures;

		void setup_mesh();

	public:

		// Constructors
		Mesh(std::vector<vertex> vertices, std::vector<GLuint> indicies, std::vector<texture> textures);

		void draw(std::shared_ptr<Shader> shader);
	};
}

#endif