#include "AudioMixer.h"
#include "Sound.h"
#include <thread>
#include <SDL_Mixer.h>
#include <SDL.h>
#include <map>
#include <iostream>
#include <functional>
#include <mutex>
#include <stack>
namespace dae
{
	class AudioMixer::AudioMixerImpl final : public Audio
	{
	public:
		AudioMixerImpl()
		{
			SDL_Init(SDL_INIT_AUDIO);
			Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG);
			Mix_AllocateChannels(32);
			Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
			Mix_ChannelFinished(&AudioMixer::AudioMixerImpl::FinishedPlayCallback);
			for (uint32_t index{}; index < 1; ++index)
			{
				m_ThreadPool.emplace_back([&](std::stop_token stopToken)
										  {
											  while (!stopToken.stop_requested())
											  {
												  Sound* sound;
												  {
													  std::unique_lock queueLock{ m_QueueMutex };

													  m_SoundAvailable.wait(queueLock, [&]() { return !m_SoundQueue.empty() || stopToken.stop_requested(); });

													  if (stopToken.stop_requested())
														  return;

													  sound = m_SoundQueue.top();
													  m_SoundQueue.pop();
												  }

												  std::unique_lock channelGuard{ m_ChannelMutex };
												  int channel = -1;
												  if (m_SoundChannels.find(sound->GetID()) != m_SoundChannels.end())
												  {
													  channel = m_SoundChannels[sound->GetID()];
												  }
												  Mix_Chunk* chunk = Mix_LoadWAV(("Data/" + sound->GetPath()).c_str());
												  if (!chunk)
												  {
													  std::cerr << "failed to load audio file " + sound->GetPath();
													  return;
												  }
												  if (Mix_Playing(channel))
													  Mix_HaltChannel(channel);
												  channel = Mix_PlayChannel(channel, chunk, 0);
												  m_SoundChannels[sound->GetID()] = channel;
											  }
										  });
			}
		}
		~AudioMixerImpl()
		{
			for (std::jthread& thread : m_ThreadPool)
				thread.request_stop();

			m_SoundQueue = {};

			m_SoundAvailable.notify_all();

			for (std::jthread& thread : m_ThreadPool)
				thread.join();
		}

		AudioMixerImpl(const AudioMixerImpl&) = delete;
		AudioMixerImpl(AudioMixerImpl&&) noexcept = delete;
		AudioMixerImpl& operator=(const AudioMixerImpl&) = delete;
		AudioMixerImpl& operator=(AudioMixerImpl&&) noexcept = delete;

		void Play(Sound* sound) override
		{
			{
				std::unique_lock queueLock{ m_QueueMutex };
				m_SoundQueue.push(sound);
			}
			m_SoundAvailable.notify_one();
		}

		void Pause(Sound* sound) override
		{
			std::unique_lock channelGuard{ m_ChannelMutex };
			Mix_Pause(m_SoundChannels[sound->GetID()]);
		}

		void Resume(Sound* sound) override
		{
			std::unique_lock channelGuard{ m_ChannelMutex };
			Mix_Resume(m_SoundChannels[sound->GetID()]);
		}

		void Stop(Sound* sound) override
		{
			std::unique_lock channelGuard{ m_ChannelMutex };
			Mix_HaltChannel(m_SoundChannels[sound->GetID()]);
		}

		void StopAllSounds() override
		{
			Mix_HaltChannel(-1);
		}

		static void FinishedPlayCallback(int channel)
		{
			std::unique_lock freeMutex{ m_FreeChunkMutex };
			if (Mix_Chunk* chunk = Mix_GetChunk(channel))
				Mix_FreeChunk(chunk);
		}

	private:
		inline static std::mutex m_FreeChunkMutex{};
		std::condition_variable m_SoundAvailable{};
		std::vector<std::jthread> m_ThreadPool;
		std::stack<Sound*> m_SoundQueue;
		std::map<size_t, int> m_SoundChannels{};
		std::mutex m_ChannelMutex{};
		std::mutex m_QueueMutex{};
	};

	AudioMixer::~AudioMixer()
	{
	}

	AudioMixer::AudioMixer() : m_ImplPtr{ std::make_unique<AudioMixerImpl>() }
	{
	}

	void AudioMixer::Play(Sound* sound)
	{
		m_ImplPtr->Play(sound);
	}

	void AudioMixer::Pause(Sound* sound)
	{
		m_ImplPtr->Pause(sound);
	}

	void AudioMixer::Resume(Sound* sound)
	{
		m_ImplPtr->Resume(sound);
	}

	void AudioMixer::Stop(Sound* sound)
	{
		m_ImplPtr->Stop(sound);
	}

	void AudioMixer::StopAllSounds()
	{
		m_ImplPtr->StopAllSounds();
	}
}