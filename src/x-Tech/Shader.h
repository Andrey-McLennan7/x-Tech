#pragma once

#include <x-Tech/Resource.h>
#include <rend/rend.h>

#include <memory>

namespace xTech
{
	class Shader : public Resource
	{
	// Private data members
	private:

		std::shared_ptr<rend::Shader> m_shader;

	// Public member functions
	public:

		virtual void on_load() override;
	};
}