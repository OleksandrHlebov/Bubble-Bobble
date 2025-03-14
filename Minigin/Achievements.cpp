#include "Achievements.h"
#include "GameEvent.h"
#include "Score.h"
#include <iostream>
#include "SteamAchievements.h"

void dae::AchievementComponent::Start()
{
	using namespace std::placeholders;
	GameEvent::Bind("OnScoreChanged", [this](GameEvent* gameEvent) 
		{
			if (OnScoreChanged* scoreChangedEvent = dynamic_cast<OnScoreChanged*>(gameEvent))
			{
				m_HighestScore = std::max(m_HighestScore, scoreChangedEvent->NewScore);
				static bool achieved{};
				if (g_SteamAchievements && m_HighestScore >= 500 && !achieved)
				{
					g_SteamAchievements->SetAchievement("ACH_WIN_ONE_GAME");
					achieved = true;
				}
			}
		});
}

