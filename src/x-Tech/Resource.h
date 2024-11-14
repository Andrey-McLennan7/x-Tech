#pragma once

#include <string>

namespace xTech
{
	class Resource
	{
	// Private data memebers
	private:

		std::string m_path;

	// Private memebers functions
	private:

		void load();

	// Public members functions
	public:
		
		virtual void on_load() = 0;
		virtual std::string get_path() const;

		friend class Cache;
	};
}