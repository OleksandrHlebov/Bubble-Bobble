#pragma once
#include <memory>
#include "AIType.h"

namespace dae
{
	class GameObject;
	class AIState
	{
	public:
		AIState(GameObject* character, const AIType& type) : m_Character{ character }, m_Type{ type } {}
		virtual ~AIState() {}

		AIState(const AIState&) = delete;
		AIState(AIState&&) noexcept = delete;
		AIState& operator=(const AIState&) = delete;
		AIState& operator=(AIState&&) noexcept = delete;

		virtual void OnEnter() {}
		virtual std::unique_ptr<AIState> Update(float deltaTime);
		virtual void OnExit() {}

		static void TransitionState(std::unique_ptr<AIState>& owningState, std::unique_ptr<AIState> newState);

	protected:
		GameObject* GetCharacter() { return m_Character; }
		const AIType& GetType() { return m_Type; }

	private:
		GameObject* m_Character;
		const AIType& m_Type;
	};
}