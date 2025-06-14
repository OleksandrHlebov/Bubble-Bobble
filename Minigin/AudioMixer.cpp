#include "AudioMixer.h"
#include "Sound.h"
#include <thread>
#include <SDL_Mixer.h>
#include <SDL.h>
#include <map>
#include <iostream>
#include <functional>
#include <mutex>
#include <algorithm>
#include <queue>
#include <set>
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
												  {
													  Sound* sound{ nullptr };
													  std::unique_lock queueLock{ m_QueueMutex };

													  m_SoundAvailable.wait(queueLock, [&]() { return !m_SoundQueue.empty() || stopToken.stop_requested(); });

													  while (!m_SoundQueue.empty())
													  {
														  if (stopToken.stop_requested())
															  return;

														  sound = m_SoundQueue.front();
														  m_SoundQueue.pop();
														  queueLock.unlock();

														  if (sound->IsMusic())
														  {
															  if (m_CurrentMusic.second)
																  Mix_FreeMusic(m_CurrentMusic.second);
															  m_CurrentMusic.first = sound;
															  m_CurrentMusic.second = Mix_LoadMUS(sound->GetPath().c_str());
															  if (!m_CurrentMusic.second)
															  {
																  std::cerr << "failed to open music " << sound->GetPath() << " " << Mix_GetError() << std::endl;
															  }
															  Mix_VolumeMusic(static_cast<int8_t>(sound->GetVolume() * m_Volume * MIX_MAX_VOLUME));
															  Mix_PlayMusic(m_CurrentMusic.second, sound->GetLoops());
															  continue;
														  }

														  std::unique_lock channelGuard{ m_ChannelMutex };
														  int channel = -1;
														  Mix_Chunk* chunk{ nullptr };
														  // if sound was played before it already has a channel assigned to it
														  if (m_SoundChannels.find(sound->GetID()) != m_SoundChannels.end())
														  {
															  channel = m_SoundChannels[sound->GetID()];
															  // chunk might still be in memory from before
															  // if sound was requested to play again while it is still playing
															  if (m_ChannelChunks[channel])
																  chunk = m_ChannelChunks[channel];
														  }
														  // if chunk was not found in cache
														  // then load it
														  if (!chunk)
														  {
															  chunk = Mix_LoadWAV((sound->GetPath()).c_str());

															  if (!chunk)
															  {
																  std::cerr << "failed to load audio file " + sound->GetPath();
																  return;
															  }
														  }
														  channel = Mix_PlayChannel(channel, chunk, sound->GetLoops());
														  Mix_Volume(channel, static_cast<int8_t>(sound->GetVolume() * MIX_MAX_VOLUME));
														  if (m_ChannelChunks.contains(channel))
														  {
															  if (m_ChannelChunks[channel] != chunk)
															  {
																  Mix_FreeChunk(m_ChannelChunks[channel]);
																  m_ChannelChunks.erase(channel);
															  }
															  if (auto it = std::find_if(m_SoundChannels.begin(), m_SoundChannels.end(), [channel](const std::pair<size_t, int>& pair)
																						 {
																							 return pair.second == channel;
																						 }); it != m_SoundChannels.end())
																  m_SoundChannels.erase(it);
														  }
														  // cache chunk for cleanup
														  m_ChannelChunks[channel] = chunk;
														  // link sound and assigned to it channel
														  m_SoundChannels[sound->GetID()] = channel;
														  queueLock.lock();
													  }
												  }

												  std::unique_lock freeLock{ m_FreeChunkMutex };
												  if (stopToken.stop_requested())
													  return;
												  std::set<int> channelsToFree{ m_ChannelsToFree };
												  while (!channelsToFree.empty() && !stopToken.stop_requested())
												  {
													  int channelToFree{ *channelsToFree.begin() };
													  channelsToFree.erase(channelToFree);

													  if (Mix_Playing(channelToFree))
														  continue;

													  m_ChannelsToFree.erase(channelToFree);

													  if (m_ChannelChunks.contains(channelToFree))
													  {
														  Mix_FreeChunk(m_ChannelChunks[channelToFree]);
														  m_ChannelChunks.erase(channelToFree);
													  }
												  }
											  }
										  });
			}
		}
		~AudioMixerImpl()
		{
			Mix_ChannelFinished(nullptr);
			Mix_HaltChannel(-1);

			for (std::jthread& thread : m_ThreadPool)
				thread.request_stop();

			m_SoundQueue = {};

			m_SoundAvailable.notify_all();

			for (std::jthread& thread : m_ThreadPool)
				thread.join();

			for (auto [channel, chunk] : m_ChannelChunks)
			{
				Mix_FreeChunk(chunk);
			}
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

		void SetMasterVolume(float volume) override
		{
			volume = std::clamp(volume, .0f, 1.f);
			Mix_MasterVolume(static_cast<int8_t>(volume * MIX_MAX_VOLUME));
			if (m_CurrentMusic.second)
				Mix_VolumeMusic(static_cast<int8_t>(m_CurrentMusic.first->GetVolume() * volume * MIX_MAX_VOLUME));
			m_Volume = volume;
		}

		float GetMasterVolume() override
		{
			return m_Volume;
		}

		static void FinishedPlayCallback(int channel)
		{
			std::unique_lock freeLock{ m_FreeChunkMutex };
			m_ChannelsToFree.insert(channel);
		}


	private:

		inline static std::mutex m_FreeChunkMutex{};
		inline static std::set<int> m_ChannelsToFree;
		inline static std::condition_variable m_SoundAvailable{};
		std::map<int, Mix_Chunk*> m_ChannelChunks;
		std::mutex m_ChannelMutex{};
		std::vector<std::jthread> m_ThreadPool;
		std::queue<Sound*> m_SoundQueue;
		std::map<size_t, int> m_SoundChannels{};
		std::mutex m_QueueMutex{};
		std::pair<Sound*, Mix_Music*> m_CurrentMusic{};

		float m_Volume{ 1.f };
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

	void AudioMixer::SetMasterVolume(float volume)
	{
		m_ImplPtr->SetMasterVolume(volume);
	}

	float AudioMixer::GetMasterVolume()
	{
		return m_ImplPtr->GetMasterVolume();
	}

}