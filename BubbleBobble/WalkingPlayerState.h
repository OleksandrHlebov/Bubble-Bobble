#pragma once
#include "PlayerState.h"
#include <string>


namespace dae
{
	class Render2DComponent; 
	class MovementComponent;
	class WalkingPlayerState final : public PlayerState
	{
	public:
		WalkingPlayerState(const PlayerType& type, GameObject* player) : PlayerState(type, player) {}
		~WalkingPlayerState() = default;
		
		WalkingPlayerState(const WalkingPlayerState&) 				= delete;
		WalkingPlayerState(WalkingPlayerState&&) noexcept 			= delete;
		WalkingPlayerState& operator=(const WalkingPlayerState&) 	 	= delete;
		WalkingPlayerState& operator=(WalkingPlayerState&&) noexcept 	= delete;

		void OnEnter() override;

		std::unique_ptr<PlayerState> Update(float deltaTime) override;

		void OnExit() override;

	private:
		MovementComponent* m_MovementComponent;
		Render2DComponent* m_RenderComponent;
	};
}