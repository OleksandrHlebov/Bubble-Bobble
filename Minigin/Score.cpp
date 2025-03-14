#include "Score.h"
#include "TextComponent.h"
#include "GameObject.h"

void dae::Score::TrackGameObject(GameObject* gameObject)
{
	m_TrackedGameObject = gameObject;
}

void dae::Score::HandleScoreChange(GameEvent* gameEvent)
{
	if (auto scoreChange = dynamic_cast<ScoreChange*>(gameEvent))
	{
		if (scoreChange->Instigator == m_TrackedGameObject)
		{
			m_Score += scoreChange->Amount;
			m_UpdateScore = true;
		}
	}
}

void dae::Score::Start()
{
	using namespace std::placeholders;
	GameEvent::Bind("ScoreChange", std::bind(&Score::HandleScoreChange, this, _1));
	UpdateScore();
}

void dae::Score::UpdateScore()
{
	if (TextComponent* textComp = GetOwner()->GetComponent<TextComponent>())
	{
		textComp->SetText("SCORE: " + std::to_string(m_Score));
	}
}

void dae::Score::Update(float deltaTime)
{
	(void)deltaTime;
	if (m_UpdateScore)
	{
		GameEvent::Dispatch<OnScoreChanged>(m_Score);
		UpdateScore();
		m_UpdateScore = false;
	}
}
