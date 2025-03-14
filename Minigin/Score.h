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

		void HandleScoreChange(const GameEvent* gameEvent);

	private:
		void Start() override;
		void UpdateScore();

		GameObject* m_TrackedGameObject;

		int m_Score{};
	};
}