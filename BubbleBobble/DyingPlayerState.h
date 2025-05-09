#pragma once
#include "PlayerState.h"
#include <string>

namespace dae
{
	class Animation2DComponent;
	class DyingPlayerState final : public PlayerState
	{
	public:
		DyingPlayerState(GameObject* player) : PlayerState(player) {}
		~DyingPlayerState() = default;
		
		DyingPlayerState(const DyingPlayerState&) 				= delete;
		DyingPlayerState(DyingPlayerState&&) noexcept 			= delete;
		DyingPlayerState& operator=(const DyingPlayerState&) 	 	= delete;
		DyingPlayerState& operator=(DyingPlayerState&&) noexcept 	= delete;

		void OnEnter() override;

		std::unique_ptr<PlayerState> Update(float deltaTime) override;

		void OnExit() override;

	private:
		inline static const std::string m_DyingPath[]{ "Textures/Bub_dying.png", "Textures/Bob_dying.png" };

		Animation2DComponent* m_AnimComponent;
	};
}