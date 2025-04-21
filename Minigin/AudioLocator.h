#pragma once
#include <cstdint>

namespace dae
{
	class Sound;
	class Audio
	{
	public:
		virtual ~Audio() {}
		virtual void Play(Sound* sound) = 0;
		virtual void Pause(Sound* sound) = 0;
		virtual void Resume(Sound* sound) = 0;
		virtual void Stop(Sound* sound) = 0;
		virtual void StopAllSounds() = 0;
		virtual void SetMasterVolume(float volume) = 0;

		virtual float GetMasterVolume() = 0;
	};

	class Logger final : public Audio
	{
	public:
		Logger() = delete;
		Logger(Audio* service) : m_Service{ service }
		{
		}
		~Logger() = default;
		
		Logger(const Logger&) 				= delete;
		Logger(Logger&&) noexcept 			= delete;
		Logger& operator=(const Logger&) 	 	= delete;
		Logger& operator=(Logger&&) noexcept 	= delete;

		void Play(Sound* sound) override;
		void Pause(Sound* sound) override;
		void Resume(Sound* sound) override;
		void Stop(Sound* sound) override;
		void StopAllSounds() override;
		void SetMasterVolume(float volume) override;

		float GetMasterVolume() override;

	private:
		Audio* m_Service;
	};

	class AudioLocator final
	{
	public:
		AudioLocator() = default;
		~AudioLocator() = default;

		AudioLocator(const AudioLocator&) = delete;
		AudioLocator(AudioLocator&&) noexcept = delete;
		AudioLocator& operator=(const AudioLocator&) = delete;
		AudioLocator& operator=(AudioLocator&&) noexcept = delete;

		static Audio* GetService() { return m_Service; }
		static void		Provide(Audio* service) { m_Service = service; }

	private:
		class NullAudio final : public Audio
		{
		public:
			NullAudio() = default;
			~NullAudio() = default;
			void Play(Sound* sound) override
			{
				(void)sound;
			}
			void Pause(Sound* sound) override
			{
				(void)sound;
			}
			void Resume(Sound* sound) override
			{
				(void)sound;
			}
			void Stop(Sound* sound) override
			{
				(void)sound;
			}
			void StopAllSounds() override
			{

			}
			void SetMasterVolume(float volume) override
			{
				(void)volume;
			}

			float GetMasterVolume() override
			{
				return -1.f;
			}
		};

		inline static NullAudio m_NullService{};
		inline static Audio* m_Service{ &m_NullService };
	};
}