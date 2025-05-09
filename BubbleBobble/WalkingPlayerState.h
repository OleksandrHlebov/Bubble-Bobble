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
		WalkingPlayerState(GameObject* player) : PlayerState(player) {}
		~WalkingPlayerState() = default;
		
		WalkingPlayerState(const WalkingPlayerState&) 				= delete;
		WalkingPlayerState(WalkingPlayerState&&) noexcept 			= delete;
		WalkingPlayerState& operator=(const WalkingPlayerState&) 	 	= delete;
		WalkingPlayerState& operator=(WalkingPlayerState&&) noexcept 	= delete;

		void OnEnter() override;

		std::unique_ptr<PlayerState> Update(float deltaTime) override;

		void OnExit() override;

	private:
		inline static const std::string m_WalkingPath[]{ "Textures/Bub_walking.png", "Textures/Bob_walking.png" };

		MovementComponent* m_MovementComponent;
		Render2DComponent* m_RenderComponent;
	};
}