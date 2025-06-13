#pragma once
#include "PlayerState.h"
#include <string>

namespace dae
{
	class Animation2DComponent;
	class DyingPlayerState final : public PlayerState
	{
	public:
		DyingPlayerState(const PlayerType& type, GameObject* player) : PlayerState(type, player) {}
		~DyingPlayerState() = default;
		
		DyingPlayerState(const DyingPlayerState&) 				= delete;
		DyingPlayerState(DyingPlayerState&&) noexcept 			= delete;
		DyingPlayerState& operator=(const DyingPlayerState&) 	 	= delete;
		DyingPlayerState& operator=(DyingPlayerState&&) noexcept 	= delete;

		void OnEnter() override;

		std::unique_ptr<PlayerState> Update(float deltaTime) override;

		void OnExit() override;

	private:
		Animation2DComponent* m_AnimComponent;
	};
}