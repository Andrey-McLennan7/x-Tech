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
	Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
	{
		std::string vertexCode;
		std::string fragmentCode;

		std::stringstream vertexShaderStream;
		std::stringstream fragmentShaderStream;

		std::ifstream vertexShaderFile;
		std::ifstream fragmentShaderFile;

		const char* vertexShaderData;
		const char* fragmentShaderData;

		vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			// Open Files
			vertexShaderFile.open(vertexPath.c_str());
			fragmentShaderFile.open(fragmentPath.c_str());

			// Read Files
			vertexShaderStream << vertexShaderFile.rdbuf();
			fragmentShaderStream << fragmentShaderFile.rdbuf();

			// Close Files
			vertexShaderFile.close();
			fragmentShaderFile.close();

			// Read as a string
			vertexCode = vertexShaderStream.str();
			fragmentCode = fragmentShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			throw std::runtime_error("ERROR::FAILED TO OPEN FILE");
		}

		#ifdef _WIN32
			vertexCode = "#version 330 core\n" + vertexCode;
			fragmentCode = "#version 330 core\n" + fragmentCode;
		#endif

		// Read as constant character
		vertexShaderData = vertexCode.c_str();
		fragmentShaderData = fragmentCode.c_str();

		// Vertex
		this->compile_shader(this->m_vertex, vertexShaderData, GL_VERTEX_SHADER, "VERTEX");

		// Fragment
		this->compile_shader(this->m_fragment, fragmentShaderData, GL_FRAGMENT_SHADER, "FRAGMENT");

		// Program
		this->create_shader_program();
	}

	Shader::~Shader()
	{}

	void Shader::compile_shader(GLuint& shader, const char* shaderData, GLenum type)
	{
		this->compile_shader(shader, shaderData, type, "");
	}

	void Shader::compile_shader(GLuint& shader, const char* shaderData, GLenum type, std::string shaderName)
	{
		int success{ 0 };
		char infolog[1024];

		shader = glCreateShader(type);
		glShaderSource(shader, 1, &shaderData, NULL);
		glCompileShader(shader);

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infolog);

			throw std::runtime_error("ERROR::FAILED TO COMPILE " + shaderName + " SHADER::" + std::string(infolog));
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