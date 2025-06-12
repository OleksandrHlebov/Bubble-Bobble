#pragma once
#include "AIState.h"
#include "GameEvent.h"

namespace dae
{
	class TrappedAIState final : public AIState
	{
	public:
		TrappedAIState(GameObject* owner, const AIType& type)
			: AIState(owner, type)
			{}

		void OnEnter() override;

		std::unique_ptr<AIState> Update(float deltaTime) override;

		void OnExit() override;

		void HandleOverlap(GameEvent*);

	private:
		EventHandler m_OverlapHandler{ std::bind(&TrappedAIState::HandleOverlap, this, std::placeholders::_1) };

		const float m_MinY{ 50 };
		const float m_TimeToEscape{ 6.f };
		float m_EscapeTimer{};
		float m_FloatingSpeed{};
		bool m_Died{};
	};
}
