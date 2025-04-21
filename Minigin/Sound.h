#pragma once
#include "AudioLocator.h"
#include <string>
#include <unordered_map>

namespace dae
{
	class Sound final
	{
	public:
		using SoundMap = std::unordered_map<size_t, std::string>;

		Sound(const std::string& filepath) : m_ID{ std::hash<const char*>{}(filepath.c_str()) }
		{
			m_SoundMap[m_ID] = filepath;
		}
		~Sound() = default;

		Sound(const Sound&) = delete;
		Sound(Sound&&) noexcept = delete;
		Sound& operator=(const Sound&) = delete;
		Sound& operator=(Sound&&) noexcept = delete;

		void Play()
		{
			AudioLocator::GetService()->Play(this);
		}
		void Pause()
		{
			AudioLocator::GetService()->Pause(this);
		}
		void Stop()
		{
			AudioLocator::GetService()->Stop(this);
		}

		const std::string& GetPath() { return m_SoundMap[m_ID]; }

		size_t GetID() { return m_ID; }

	private:
		size_t m_ID;

		inline static SoundMap m_SoundMap;
	};
}