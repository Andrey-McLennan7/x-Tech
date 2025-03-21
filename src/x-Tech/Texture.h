#pragma once

#ifndef X_TECH_TEXTURE_H
#define X_TECH_TEXTURE_H

#include <x-Tech/Resource.h>
#include <rend/rend.h>

#include <memory>

namespace xTech
{
	class Texture : public Resource
	{
		// Private data members
	private:

		std::shared_ptr<rend::Texture> m_texture;

		// Public member functions
	public:

		virtual void on_load() override;
	};
}

#endif