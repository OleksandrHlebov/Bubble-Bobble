#pragma once
#include "Component.h"
#include "steam_api_common.h"

namespace dae
{
	struct GameEvent;
	class AchievementComponent final : public Component
	{
	public:
		AchievementComponent() = delete;
		AchievementComponent(GameObject* owner) : Component(owner)
		{
		}
		~AchievementComponent() = default;
		
		AchievementComponent(const AchievementComponent&) 				= delete;
		AchievementComponent(AchievementComponent&&) noexcept 			= delete;
		AchievementComponent& operator=(const AchievementComponent&) 	 	= delete;
		AchievementComponent& operator=(AchievementComponent&&) noexcept 	= delete;

		void HandleScoreChange(GameEvent* gameEvent);

	private:
		void Start() override;

		int m_HighestScore{};
	};
}