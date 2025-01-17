#pragma once

#ifndef X_TECH_SOUND_SOURCE_H
#define X_TECH_SOUND_SOURCE_H

#include "Component.h"

#include <AL/al.h>

#include <memory>

namespace xTech
{
	class Audio;

	class SoundSource : public Component
	{
	// Private data members
	private:

		ALuint m_id;

		std::shared_ptr<Audio> m_audio;

		bool m_loop;

	// Public member functions
	public:

		virtual void on_initialize() override;
		virtual void on_tick() override;

		void play();

		void audio(const std::string& path);
		void audio(std::shared_ptr<Audio> audio);
		std::shared_ptr<Audio> audio() const;

		void loop(bool loop);
		bool loop() const;
	};
}

#endif