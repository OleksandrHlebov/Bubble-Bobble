#pragma once
#include "AIState.h"

#include <glm.hpp>

namespace dae
{
	struct GameEvent;
	class MovementComponent;
	class Render2DComponent;
	class WalkingAIState final : public AIState
	{
	public:
		WalkingAIState(GameObject* character, const AIType& type) : AIState(character, type) {}
		~WalkingAIState() = default;

		WalkingAIState(const WalkingAIState&) = delete;
		WalkingAIState(WalkingAIState&&) noexcept = delete;
		WalkingAIState& operator=(const WalkingAIState&) = delete;
		WalkingAIState& operator=(WalkingAIState&&) noexcept = delete;

		void OnEnter() override;

		std::unique_ptr<AIState> Update(float deltaTime) override;

		void OnExit() override;

		void HandleOverlap(GameEvent* );

	private:
		MovementComponent* m_MovementComponent;
		Render2DComponent* m_RenderComponent;
		glm::vec3 m_Direction{ -1, .0f, .0f };
	};
}
