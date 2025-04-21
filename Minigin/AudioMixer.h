#pragma once
#include "AudioLocator.h"
#include <memory>

namespace dae
{
	class AudioMixer final : public Audio
	{
	public:
		AudioMixer();
		~AudioMixer();

		AudioMixer(const AudioMixer&) = delete;
		AudioMixer(AudioMixer&&) noexcept = delete;
		AudioMixer& operator=(const AudioMixer&) = delete;
		AudioMixer& operator=(AudioMixer&&) noexcept = delete;

		void Play(Sound* sound) override;

		void Pause(Sound* sound) override;

		void Resume(Sound* sound) override;

		void Stop(Sound* sound) override;

		void StopAllSounds() override;

	private:
		class AudioMixerImpl;
		std::unique_ptr<AudioMixerImpl> m_ImplPtr;
	};
}