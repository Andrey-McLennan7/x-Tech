#include "SoundSource.h"
#include "Transform.h"
#include "Audio.h"

#include <stdexcept>
#include <vector>

namespace xTech
{
	void SoundSource::on_initialize()
	{
		alGenSources(1, &this->m_id);
	}

	void SoundSource::on_tick()
	{
		glm::vec3 position{ this->transform()->m_position };

		alSource3f(this->m_id, AL_POSITION, position.x, position.y, position.z);
	}

	void SoundSource::play()
	{
		alSourcePlay(this->m_id);

		/*while (true)
		{
			int state{ 0 };
			alGetSourcei(this->m_id, AL_SOURCE_STATE, &state);

			if (state != AL_PLAYING)
			{
				break;
			}
		}*/
	}

	void SoundSource::audio(std::shared_ptr<Audio> audio)
	{
		this->m_audio = audio;

		alSourcei(this->m_id, AL_BUFFER, audio->m_id);
	}
}