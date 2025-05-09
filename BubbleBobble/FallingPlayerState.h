#pragma once
#include "PlayerState.h"
#include <string>

namespace dae
{
	class MovementComponent;
	class Render2DComponent;
	class FallingPlayerState final : public PlayerState
	{
	public:
		FallingPlayerState(GameObject* player) : PlayerState(player) {}
		~FallingPlayerState() = default;

		FallingPlayerState(const FallingPlayerState&) = delete;
		FallingPlayerState(FallingPlayerState&&) noexcept = delete;
		FallingPlayerState& operator=(const FallingPlayerState&) = delete;
		FallingPlayerState& operator=(FallingPlayerState&&) noexcept = delete;

		void OnEnter() override;

		std::unique_ptr<PlayerState> Update(float deltaTime) override;

		void OnExit() override;

	private:
		inline static const std::string m_JumpingPath[]{ "Textures/Bub_jumping.png", "Textures/Bob_jumping.png" };

		MovementComponent* m_MovementComponent;
		Render2DComponent* m_RenderComponent;

	};

}