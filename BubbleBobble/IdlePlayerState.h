#pragma once
#include "PlayerState.h"
#include <string>

namespace dae
{
	class MovementComponent;
	class IdlePlayerState final : public PlayerState
	{
	public:
		IdlePlayerState(const PlayerType& type, GameObject* player) : PlayerState(type, player) {}
		~IdlePlayerState() = default;
		
		IdlePlayerState(const IdlePlayerState&) 				= delete;
		IdlePlayerState(IdlePlayerState&&) noexcept 			= delete;
		IdlePlayerState& operator=(const IdlePlayerState&) 	 	= delete;
		IdlePlayerState& operator=(IdlePlayerState&&) noexcept 	= delete;

		void OnEnter() override;

		std::unique_ptr<PlayerState> Update(float deltaTime) override;

		void OnExit() override;

	private:
		MovementComponent* m_MovementComponent;
	};
}