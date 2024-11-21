#include "Resource.h"

#include <AL/al.h>

#include <string>
#include <vector>

namespace xTech
{
	class SoundSource;

	class Audio : public Resource
	{
	// Private data members
	private:

		ALuint m_id;

	// Private member functions
	private:

		void load_ogg(const std::string& path, std::vector<unsigned char>& buffer, ALenum& format, ALsizei& frequency);

	// Public member functions
	public:

		virtual void on_load() override;

		friend class SoundSource;
	};
}