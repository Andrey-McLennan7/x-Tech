#include "Shader.h"

#include <SDL2/SDL_log.h>
#include <SDL2/SDL_error.h>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace xTech
{
	void Shader::on_load()
	{
		this->m_shader = std::make_shared<rend::Shader>(this->get_path() + ".vert", this->get_path() + ".frag");
	}

	void Shader::use()
	{
		this->m_shader->use();
	}

	void Shader::unuse()
	{
		this->m_shader->unuse();
	}

	void Shader::set_float(const std::string& attribute, float value) const
	{
		this->m_shader->set_float(attribute, value);
	}

	void Shader::set_int(const std::string& attribute, int value) const
	{
		this->m_shader->set_int(attribute, value);
	}

	void Shader::set_bool(const std::string& attribute, bool value) const
	{
		this->m_shader->set_bool(attribute, value);
	}

	void Shader::set_vec3(const std::string& attribute, float x, float y, float z) const
	{
		this->m_shader->set_vec3(attribute, x, y, z);
	}

	void Shader::set_vec3(const std::string& attribute, const glm::vec3& value) const
	{
		this->m_shader->set_vec3(attribute, value);
	}

	void Shader::set_vec3(const std::string& attribute, const float* value) const
	{
		this->m_shader->set_vec3(attribute, value);
	}

	void Shader::set_vec4(const std::string& attribute, float x, float y, float z, float w) const
	{
		this->m_shader->set_vec4(attribute, x, y, z, w);
	}

	void Shader::set_vec4(const std::string& attribute, const glm::vec4& value) const
	{
		this->m_shader->set_vec4(attribute, value);
	}

	void Shader::set_vec4(const std::string& attribute, const float* value) const
	{
		this->m_shader->set_vec4(attribute, value);
	}

	void Shader::set_mat4(const std::string& attribute, const glm::mat4& value) const
	{
		this->m_shader->set_mat4(attribute, value);
	}

	std::shared_ptr<rend::Shader> Shader::shader() const
	{
		return this->m_shader;
	}
}