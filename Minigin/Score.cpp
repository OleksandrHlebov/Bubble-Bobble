#include "Score.h"
#include "TextComponent.h"
#include "GameObject.h"

void dae::Score::TrackGameObject(GameObject* gameObject)
{
	m_TrackedGameObject = gameObject;
}

void dae::Score::HandleScoreChange(GameEvent* gameEvent)
{
	if (auto scoreChange = dynamic_cast<const ScoreChange*>(gameEvent))
	{
		if (scoreChange->Instigator == m_TrackedGameObject)
		{
			m_Score += scoreChange->Amount;
			UpdateScore();
		}
	}
}

void dae::Score::Start()
{
	using namespace std::placeholders;
	GameEvent::Bind("ScoreChange", std::bind(&Score::HandleScoreChange, this, _1));
	UpdateScore();
	EventDispatcher::GetInstance().UnBind("ScoreChange", std::bind(&Score::HandleScoreChange, this, _1));
}

void dae::Score::UpdateScore()
{
	if (TextComponent* textComp = GetOwner()->GetComponent<TextComponent>())
	{
		textComp->SetText("SCORE: " + std::to_string(m_Score));
	}
}
