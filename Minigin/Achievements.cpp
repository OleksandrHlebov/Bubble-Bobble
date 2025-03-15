#include "Achievements.h"
#include "GameEvent.h"
#include "Score.h"
#include <iostream>
#include "SteamAchievements.h"

void dae::AchievementComponent::HandleScoreChange(GameEvent* gameEvent)
{
	using namespace std::placeholders;
	if (OnScoreChanged* scoreChangedEvent = dynamic_cast<OnScoreChanged*>(gameEvent))
	{
		m_HighestScore = std::max(m_HighestScore, scoreChangedEvent->NewScore);
		if (g_SteamAchievements && m_HighestScore >= 500)
		{
			g_SteamAchievements->SetAchievement("ACH_WIN_ONE_GAME");
			GameEvent::UnBind("OnScoreChanged", std::bind(&AchievementComponent::HandleScoreChange, this, _1));
		}
	}
}

void dae::AchievementComponent::Start()
{
	using namespace std::placeholders;
	GameEvent::Bind("OnScoreChanged", std::bind(&AchievementComponent::HandleScoreChange, this, _1));
}

