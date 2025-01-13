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
		alSource3f(this->m_id, AL_POSITION, this->position().x, this->position().y, this->position().z);

		if (this->m_loop)
		{
			int state{ 0 };
			alGetSourcei(this->m_id, AL_SOURCE_STATE, &state);

			if (state != AL_PLAYING)
			{
				alSourcePlay(this->m_id);
			}
		}
	}

	void SoundSource::play()
	{
		alSourcePlay(this->m_id);
	}

	void SoundSource::audio(std::shared_ptr<Audio> audio)
	{
		this->m_audio = audio;

		alSourcei(this->m_id, AL_BUFFER, audio->m_id);
	}

	std::shared_ptr<Audio> SoundSource::audio() const
	{
		if (this->m_audio)
		{
			throw std::runtime_error("ERROR::NO AUDIO SAMPLE");
		}

		return this->m_audio;
	}

	void SoundSource::loop(bool loop)
	{
		this->m_loop = loop;
	}

	bool SoundSource::loop() const
	{
		return this->m_loop;
	}
}