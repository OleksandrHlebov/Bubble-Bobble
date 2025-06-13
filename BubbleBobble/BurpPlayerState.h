#pragma once
#include "PlayerState.h"
#include <string>

namespace dae
{
	class BurpPlayerState final : public PlayerState
	{
	public:
		BurpPlayerState(const PlayerType& type, GameObject* player) : PlayerState(type, player) {}
		~BurpPlayerState() = default;
		
		BurpPlayerState(const BurpPlayerState&) 				= delete;
		BurpPlayerState(BurpPlayerState&&) noexcept 			= delete;
		BurpPlayerState& operator=(const BurpPlayerState&) 	 	= delete;
		BurpPlayerState& operator=(BurpPlayerState&&) noexcept 	= delete;

		void OnEnter() override;

		std::unique_ptr<PlayerState> Update(float deltaTime) override;

		void OnExit() override;

	private:
		float m_Timer{};
		inline static const float DELAY{ 0.3f };
	};
}