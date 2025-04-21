#pragma once
#include "Component.h"
#include "Sound.h"

namespace dae
{
	struct GameEvent;
	class AudioHandler final : public Component
	{
	public:
		AudioHandler() = delete;
		AudioHandler(GameObject* owner);
		~AudioHandler() = default;

		AudioHandler(const AudioHandler&) = delete;
		AudioHandler(AudioHandler&&) noexcept = delete;
		AudioHandler& operator=(const AudioHandler&) = delete;
		AudioHandler& operator=(AudioHandler&&) noexcept = delete;

		void HandleJumpingSound(GameEvent* event);

	private:
		Sound m_JumpSFX{ "SFX/jump.wav" };
	};
}