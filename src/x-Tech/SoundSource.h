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

		std::shared_ptr<Audio> m_audio;

		ALuint m_id;

	// Public member functions
	public:

		virtual void on_initialize() override;
		virtual void on_tick() override;

		void play();

		void audio(std::shared_ptr<Audio> audio);
	};
}