#pragma once
#include "PlayerState.h"
#include <string>

namespace dae
{
	class MovementComponent;
	class IdlePlayerState final : public PlayerState
	{
	public:
		IdlePlayerState(GameObject* player) : PlayerState(player) {}
		~IdlePlayerState() = default;
		
		IdlePlayerState(const IdlePlayerState&) 				= delete;
		IdlePlayerState(IdlePlayerState&&) noexcept 			= delete;
		IdlePlayerState& operator=(const IdlePlayerState&) 	 	= delete;
		IdlePlayerState& operator=(IdlePlayerState&&) noexcept 	= delete;

		void OnEnter() override;

		std::unique_ptr<PlayerState> Update(float deltaTime) override;

		void OnExit() override;

	private:
		inline static const std::string m_IdlePath[]{ "Textures/Bub_walking.png", "Textures/Bob_walking.png" };

		MovementComponent* m_MovementComponent;
	};
}