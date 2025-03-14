#pragma once
#include "Component.h"
#include "GameEvent.h"

namespace dae
{
	struct ScoreChange final : public GameEvent
	{
		ScoreChange() = delete;
		explicit ScoreChange(GameObject* instigator, int amount) : GameEvent("ScoreChange"), Instigator{ instigator }, Amount { amount }
		{
		}

		GameObject* Instigator;
		int Amount;
	};

	struct OnScoreChanged final : public GameEvent
	{
		OnScoreChanged() = delete;
		explicit OnScoreChanged(int newScore) : GameEvent("OnScoreChanged"), NewScore{ newScore }
		{
		}

		int NewScore;
	};

	class Score final : public Component
	{
	public:

		Score() = delete;
		Score(GameObject* owner) : Component(owner)
		{
		}
		~Score() = default;
		
		Score(const Score&) 				= delete;
		Score(Score&&) noexcept 			= delete;
		Score& operator=(const Score&) 	 	= delete;
		Score& operator=(Score&&) noexcept 	= delete;

		void TrackGameObject(GameObject* gameObject);

		void HandleScoreChange(GameEvent* gameEvent);

	private:
		void Start() override;
		void UpdateScore();
		void Update(float deltaTime) override;

		GameObject* m_TrackedGameObject;

		int m_Score{};
		bool m_UpdateScore{ true };
	};
}