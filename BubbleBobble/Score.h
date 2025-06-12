#pragma once
#include "Component.h"
#include "GameEvent.h"
#include "EventDispatcher.h"
#include <functional>

namespace dae
{
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

		EventHandler m_ScoreChangeHandler{ std::bind(&Score::HandleScoreChange, this, std::placeholders::_1) };
		GameObject* m_TrackedGameObject;

		int m_Score{};
	};
}