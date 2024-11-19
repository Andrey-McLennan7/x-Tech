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

	std::shared_ptr<rend::Shader> Shader::ID()
	{
		return this->m_shader;
	}
}