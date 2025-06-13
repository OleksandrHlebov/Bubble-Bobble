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
		FallingPlayerState(const PlayerType& type, GameObject* player) : PlayerState(type, player) {}
		~FallingPlayerState() = default;

		FallingPlayerState(const FallingPlayerState&) = delete;
		FallingPlayerState(FallingPlayerState&&) noexcept = delete;
		FallingPlayerState& operator=(const FallingPlayerState&) = delete;
		FallingPlayerState& operator=(FallingPlayerState&&) noexcept = delete;

		void OnEnter() override;

		std::unique_ptr<PlayerState> Update(float deltaTime) override;

		void OnExit() override;

	private:
		MovementComponent* m_MovementComponent;
		Render2DComponent* m_RenderComponent;

	};

}