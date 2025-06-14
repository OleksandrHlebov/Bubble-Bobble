#include "BubbleBobble.h"
#include "Score.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "PickUpComponent.h"

void dae::Score::TrackGameObject(GameObject* gameObject)
{
	m_TrackedGameObject = gameObject;
}

void dae::Score::HandleScoreChange(GameEvent* gameEvent)
{
	auto pickup = static_cast<PickupComponent::OnPickup*>(gameEvent);
	
	m_Score = BubbleBobble::Highscore += pickup->Value;
	UpdateScore();
}

void dae::Score::Start()
{
	GameEvent::Bind("OnPickup", &m_ScoreChangeHandler);
	m_Score = BubbleBobble::Highscore;
	UpdateScore();
}

void dae::Score::UpdateScore()
{
	if (TextComponent* textComp = GetOwner()->GetComponent<TextComponent>())
	{
		textComp->SetText("SCORE: " + std::to_string(m_Score));
	}
}
