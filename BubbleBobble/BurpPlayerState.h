#pragma once
#include "PlayerState.h"
#include <string>

namespace dae
{
	class BurpPlayerState final : public PlayerState
	{
	public:
		BurpPlayerState(GameObject* player) : PlayerState(player) {}
		~BurpPlayerState() = default;
		
		BurpPlayerState(const BurpPlayerState&) 				= delete;
		BurpPlayerState(BurpPlayerState&&) noexcept 			= delete;
		BurpPlayerState& operator=(const BurpPlayerState&) 	 	= delete;
		BurpPlayerState& operator=(BurpPlayerState&&) noexcept 	= delete;

		void OnEnter() override;

		std::unique_ptr<PlayerState> Update(float deltaTime) override;

		void OnExit() override;

	private:
		inline static const std::string m_BurpPath[]{ "Textures/Bub_burp.png", "Textures/Bob_burp.png" };

		float m_Timer{};
		inline static const float DELAY{ 0.3f };
	};
}