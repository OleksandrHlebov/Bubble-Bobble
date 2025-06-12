#pragma once
#include "AIState.h"
#include "GameEvent.h"
#include "MovementCommands.h"

namespace dae
{
	class DeadAIState final : public AIState
	{
	public:
		DeadAIState(GameObject* character, const AIType& type)
		: AIState(character, type)
		{}

		void OnEnter() override;

		std::unique_ptr<AIState> Update(float deltaTime) override;

		void OnExit() override;

		void HandleMorphingIntoFruit(GameEvent* );
	private:
		EventHandler m_MorphingHandler{ std::bind(&DeadAIState::HandleMorphingIntoFruit, this, std::placeholders::_1) };
		MoveCommand m_MoveCommand{ GetCharacter(), glm::vec3{ (rand() % 2) * 2 - 1, .0f, .0f } };

		const float m_LaunchStrength{ 200.f };
		const uint32_t m_MinLoops{ 2 };
		const uint32_t m_MaxLoops{ 4 };
	};
}