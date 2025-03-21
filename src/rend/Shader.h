#pragma once

#ifndef REND_SHADER_H
#define REND_SHADER_H

#include <GL/glew.h>
#include "glm/glm.hpp"

#include <string>

// Code source: https://learnopengl.com/Getting-started/Shaders

namespace rend
{
	class Shader
	{
	// Private data members
	private:

		GLuint m_id;

		GLuint m_vertex;
		GLuint m_fragment;

	// Private member functions
	private:

		void compile_shader(GLuint& shader, const char* shader_data, GLenum type);
		void compile_shader(GLuint& shader, const char* shader_data, GLenum type, std::string shader_name);
		void create_shader_program();

	// Public member functions
	public:

		// Constructor
		Shader(const std::string& vertex_path, const std::string& fragment_path);
		~Shader();

		// Shader Use
		void use() const;

		// Shader Unuse
		void unuse() const;

		// Utility uniforms
		void set_float(const std::string& attribute, float value) const;
		void set_int(const std::string& attribute, int value) const;
		void set_bool(const std::string& attribute, bool value) const;

		void set_vec3(const std::string& attribute, float x, float y, float z) const;
		void set_vec3(const std::string& attribute, const glm::vec3& value) const;
		void set_vec3(const std::string& attribute, const float* value) const;

		void set_vec4(const std::string& attribute, float x, float y, float z, float w) const;
		void set_vec4(const std::string& attribute, const glm::vec4& value) const;
		void set_vec4(const std::string& attribute, const float* value) const;

		void set_mat4(const std::string& attribute, const glm::mat4& value) const;

		GLuint ID() const;
	};
}

#endif