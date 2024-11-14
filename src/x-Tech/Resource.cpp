#include "Resource.h"

namespace xTech
{
	void Resource::load()
	{
		this->on_load();
	}

	std::string Resource::get_path() const
	{
		return this->m_path;
	}
}