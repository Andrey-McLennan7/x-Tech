#include "Shape.h"
#include "Shader.h"

#include <stdexcept>

namespace xTech
{
	void Shape::on_load()
	{
		if (this->get_path() == "QUAD")
		{
			this->m_shape = std::make_shared<rend::Quad>();
		}
		else if (this->get_path() == "CUBE")
		{
			this->m_shape = std::make_shared<rend::Cube>();
		}
		else if (this->get_path() == "TRIANGLE")
		{
			this->m_shape = std::make_shared<rend::Triangle>();
		}
		else if (this->get_path() == "PYRAMID")
		{
			this->m_shape = std::make_shared<rend::Pyramid>();
		}
		else
		{
			throw std::runtime_error("ERROR::UNKNOWN SHAPE NAME");
		}
	}
}