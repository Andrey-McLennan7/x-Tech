#pragma once

#ifndef X_TECH_CACHE_H
#define X_TECH_CACHE_H

#include "Resource.h"

#include <memory>
#include <string>
#include <vector>

namespace xTech
{
	class Cache
	{
	// Private data memebers
	private:

		std::vector<std::shared_ptr<Resource>> m_resources;

	// Public members functions
	public:
		
		template <typename T>
		std::shared_ptr<T> load(const std::string& path)
		{
			// Search for previously loaded resource
			std::vector<std::shared_ptr<Resource>>::iterator itr;
			for (itr = this->m_resources.begin(); itr != this->m_resources.end(); ++itr)
			{
				// Return it if found
				if ((*itr)->get_path() == path)
				{
					return std::dynamic_pointer_cast<T>(*itr);
				}
			}

			// Create new instance, construct and add to cache
			std::shared_ptr<T> rtn{ std::make_shared<T>() };

			rtn->m_path = "../res/" + path;
			rtn->load();

			this->m_resources.push_back(rtn);

			return rtn;
		}
	};
}

#endif