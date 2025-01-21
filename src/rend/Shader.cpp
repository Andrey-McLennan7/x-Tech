#include "Shader.h"

#include <SDL2/SDL_log.h>
#include <SDL2/SDL_error.h>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace rend
{
	Shader::Shader(const std::string& vertex_path, const std::string& fragment_path)
	{
		std::string vertex_code;
		std::string fragment_code;

		std::stringstream vertex_shader_stream;
		std::stringstream fragment_shader_stream;

		std::ifstream vertex_shader_file;
		std::ifstream fragment_shader_file;

		const char* vertex_shader_data;
		const char* fragment_shader_data;

		vertex_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fragment_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			// Open Files
			vertex_shader_file.open(vertex_path.c_str());
			fragment_shader_file.open(fragment_path.c_str());

			// Read Files
			vertex_shader_stream << vertex_shader_file.rdbuf();
			fragment_shader_stream << fragment_shader_file.rdbuf();

			// Close Files
			vertex_shader_file.close();
			fragment_shader_file.close();

			// Read as a string
			vertex_code = vertex_shader_stream.str();
			fragment_code = fragment_shader_stream.str();
		}
		catch (std::ifstream::failure e)
		{
			throw std::runtime_error("ERROR::FAILED TO OPEN FILE");
		}

		#ifdef _WIN32
			vertex_code = "#version 330 core\n" + vertex_code;
			fragment_code = "#version 330 core\n" + fragment_code;
		#endif

		// Read as constant character
		vertex_shader_data = vertex_code.c_str();
		fragment_shader_data = fragment_code.c_str();

		// Vertex
		this->compile_shader(this->m_vertex, vertex_shader_data, GL_VERTEX_SHADER, "VERTEX");

		// Fragment
		this->compile_shader(this->m_fragment, fragment_shader_data, GL_FRAGMENT_SHADER, "FRAGMENT");

		// Program
		this->create_shader_program();
	}

	Shader::~Shader()
	{}

	void Shader::compile_shader(GLuint& shader, const char* shader_data, GLenum type)
	{
		this->compile_shader(shader, shader_data, type, "");
	}

	void Shader::compile_shader(GLuint& shader, const char* shader_data, GLenum type, std::string shader_name)
	{
		int success{ 0 };
		char infolog[1024];

		shader = glCreateShader(type);
		glShaderSource(shader, 1, &shader_data, NULL);
		glCompileShader(shader);

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infolog);

			throw std::runtime_error("ERROR::FAILED TO COMPILE " + shader_name + " SHADER::" + std::string(infolog));
		}
	}

	void Shader::create_shader_program()
	{
		int success{ 0 };
		char infolog[1024];

		this->m_id = glCreateProgram();

		glAttachShader(this->m_id, this->m_vertex);
		glAttachShader(this->m_id, this->m_fragment);
		glLinkProgram(this->m_id);

		glGetProgramiv(this->m_id, GL_LINK_STATUS, &success);

		if (!success)
		{
			glGetProgramInfoLog(this->m_id, 1024, NULL, infolog);

			throw std::runtime_error("ERROR::FAILED TO COMPILE SHADER PROGRAM::" + std::string(infolog));
		}

		glDeleteShader(this->m_vertex);
		glDeleteShader(this->m_fragment);
	}

	void Shader::use() const
	{
		glUseProgram(this->m_id);
	}

	void Shader::unuse() const
	{
		glUseProgram(0);
	}

	void Shader::set_float(const std::string& attribute, float value) const
	{
		this->use();
		glUniform1f(glGetUniformLocation(this->m_id, attribute.c_str()), (GLfloat)value);
		this->unuse();
	}

	void Shader::set_int(const std::string& attribute, int value) const
	{
		this->use();
		glUniform1i(glGetUniformLocation(this->m_id, attribute.c_str()), (GLint)value);
		this->unuse();
	}

	void Shader::set_bool(const std::string& attribute, bool value) const
	{
		this->set_int(attribute, (int)value);
	}

	void Shader::set_vec3(const std::string& attribute, float x, float y, float z) const
	{
		this->use();
		glUniform3fv(glGetUniformLocation(this->m_id, attribute.c_str()), 1, glm::value_ptr(glm::vec3(x, y, z)));
		this->unuse();
	}

	void Shader::set_vec3(const std::string& attribute, const glm::vec3& value) const
	{
		this->set_vec3(attribute, value.x, value.y, value.z);
	}

	void Shader::set_vec3(const std::string& attribute, const float* value) const
	{
		this->set_vec3(attribute, value[0], value[1], value[2]);
	}

	void Shader::set_vec4(const std::string& attribute, float x, float y, float z, float w) const
	{
		this->use();
		glUniform4fv(glGetUniformLocation(this->m_id, attribute.c_str()), 1, glm::value_ptr(glm::vec4(x, y, z, w)));
		this->unuse();
	}

	void Shader::set_vec4(const std::string& attribute, const glm::vec4& value) const
	{
		this->set_vec4(attribute, value.x, value.y, value.z, value.w);
	}

	void Shader::set_vec4(const std::string& attribute, const float* value) const
	{
		this->set_vec4(attribute, value[0], value[1], value[2], value[3]);
	}

	void Shader::set_mat4(const std::string& attribute, const glm::mat4& value) const
	{
		this->use();
		glUniformMatrix4fv(glGetUniformLocation(this->m_id, attribute.c_str()), 1, GL_FALSE, glm::value_ptr(value));
		this->unuse();
	}

	GLuint Shader::ID() const
	{
		return this->m_id;
	}
}