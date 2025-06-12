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
	
	if (pickup->Player == m_TrackedGameObject)
	{
		m_Score += pickup->Value;
		UpdateScore();
	}
}

void dae::Score::Start()
{
	GameEvent::Bind("OnPickup", &m_ScoreChangeHandler);
	UpdateScore();
}

void dae::Score::UpdateScore()
{
	if (TextComponent* textComp = GetOwner()->GetComponent<TextComponent>())
	{
		textComp->SetText("SCORE: " + std::to_string(m_Score));
	}
}
