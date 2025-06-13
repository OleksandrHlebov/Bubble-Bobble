#pragma once
#include "PlayerState.h"

namespace dae
{
	class PlayerInMenuState final : public PlayerState
	{
	public:
		PlayerInMenuState(const PlayerType& type, GameObject* player) : PlayerState(type, player) {}
		~PlayerInMenuState() = default;

		PlayerInMenuState(const PlayerInMenuState&) = delete;
		PlayerInMenuState(PlayerInMenuState&&) noexcept = delete;
		PlayerInMenuState& operator=(const PlayerInMenuState&) = delete;
		PlayerInMenuState& operator=(PlayerInMenuState&&) noexcept = delete;

		void OnEnter() override
		{
		}

		std::unique_ptr<PlayerState> Update(float) override
		{
			return nullptr;
		}

		void OnExit()
		{
		}

	private:

	};
}