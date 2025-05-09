#pragma once
#include "PlayerState.h"
#include <string>

namespace dae
{
	class Render2DComponent;
	class MovementComponent;
	class JumpingPlayerState final : public PlayerState
	{
	public:
		JumpingPlayerState(GameObject* player) : PlayerState(player) {}
		~JumpingPlayerState() = default;
		
		JumpingPlayerState(const JumpingPlayerState&) 				= delete;
		JumpingPlayerState(JumpingPlayerState&&) noexcept 			= delete;
		JumpingPlayerState& operator=(const JumpingPlayerState&) 	 	= delete;
		JumpingPlayerState& operator=(JumpingPlayerState&&) noexcept 	= delete;

		void OnEnter() override;

		std::unique_ptr<PlayerState> Update(float deltaTime) override;

		void OnExit() override;

	private:
		inline static const std::string m_JumpingPath[]{ "Textures/Bub_jumping.png", "Textures/Bob_jumping.png" };

		MovementComponent* m_MovementComponent;
		Render2DComponent* m_RenderComponent;
	};
}