#pragma once
#include "Component.h"
#include "Sound.h"
#include "EventDispatcher.h"

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
		void HandleDamagedSound(GameEvent* event);

		void End() override;

		void Start() override;

	private:
		Sound m_JumpSFX{ "Data/SFX/jump.wav" };
		Sound m_Damaged{ "Data/SFX/damaged.wav" };

		EventHandler m_JumpHandler{ std::bind(&AudioHandler::HandleJumpingSound, this, std::placeholders::_1) };
		EventHandler m_DamageHandler{ std::bind(&AudioHandler::HandleDamagedSound, this, std::placeholders::_1) };
	};
}