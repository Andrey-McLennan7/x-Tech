#pragma once

#include <GL/glew.h>
#include "glm/glm.hpp"

// Reading Files
#include <string>

namespace xTech
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

		void CompileShader(GLuint& shader, const char* shaderData, GLenum type);
		void CompileShader(GLuint& shader, const char* shaderData, GLenum type, std::string shaderName);
		void CreateShaderProgram();

	// Public member functions
	public:

		// Constructor
		Shader(const char* vertexPath, const char* fragmentPath);
		~Shader();

		// Shader Use
		void use() const;

		// Shader Unuse
		void unuse() const;

		// Utility uniforms
		// Setters
		void setFloat(const std::string& attribute, float value) const;
		void setInt(const std::string& attribute, int value) const;
		void setBool(const std::string& attribute, bool value) const;

		void setVec3(const std::string& attribute, float x, float y, float z) const;
		void setVec3(const std::string& attribute, const glm::vec3& value) const;
		void setVec3(const std::string& attribute, const float* value) const;

		void setVec4(const std::string& attribute, float x, float y, float z, float w) const;
		void setVec4(const std::string& attribute, const glm::vec4& value) const;
		void setVec4(const std::string& attribute, const float* value) const;

		void setMat4(const std::string& attribute, const glm::mat4& value) const;

		// Getters
		GLuint ID() const;
	};
}