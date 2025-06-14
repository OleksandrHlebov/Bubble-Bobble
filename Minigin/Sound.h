#pragma once
#include "AudioLocator.h"
#include <string>
#include <unordered_map>
#include <algorithm>

namespace dae
{
	class Sound final
	{
	public:
		using SoundMap = std::unordered_map<size_t, std::string>;

		Sound(const std::string& filepath, int loops = 0, bool isMusic = false) 
			: m_ID{ std::hash<std::string>{}(filepath) }
			, m_IsMusic{ isMusic }
			, m_Loops{ loops }
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

		bool IsMusic() { return m_IsMusic; }

		const std::string& GetPath() { return m_SoundMap[m_ID]; }

		size_t GetID() { return m_ID; }
		int GetLoops() { return m_Loops; }

		void SetVolume(float volume) { m_Volume = std::clamp(volume, .0f, 1.f); }
		float GetVolume() { return m_Volume; }

	private:
		size_t m_ID;
		float m_Volume{ 1.f };
		int m_Loops;
		bool m_IsMusic;

		inline static SoundMap m_SoundMap;
	};
}