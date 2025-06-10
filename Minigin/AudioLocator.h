#pragma once
#include <cstdint>
#include <memory>

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
		Logger(std::unique_ptr<Audio>&& service) : m_Service{ std::move(service) }
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
		std::unique_ptr<Audio> m_Service;
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

		static Audio* GetService() { return m_Service.get(); }
		static void		Provide(std::unique_ptr<Audio>&& service) 
		{ 
			if (service)
				m_Service = std::move(service);
			else
				m_Service.reset(&m_NullService); 
		}

	private:
		class NullAudio final : public Audio
		{
		public:
			NullAudio() = default;
			~NullAudio() = default;
			void Play(Sound*) override
			{
			}
			void Pause(Sound*) override
			{
			}
			void Resume(Sound*) override
			{
			}
			void Stop(Sound*) override
			{
			}
			void StopAllSounds() override
			{

			}
			void SetMasterVolume(float) override
			{
			}

			float GetMasterVolume() override
			{
				return -1.f;
			}
		};

		inline static NullAudio m_NullService{};
		inline static std::unique_ptr<Audio> m_Service{ &m_NullService };
	};
}