#pragma once
#include "AIState.h"

#include <glm.hpp>
#include "EventDispatcher.h"
#include "GameEvent.h"

namespace dae
{
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

		void HandleOverlap(GameEvent*);

	private:
		EventHandler m_OverlapHandler{ std::bind(&WalkingAIState::HandleOverlap, this, std::placeholders::_1) };
		MovementComponent* m_MovementComponent;
		Render2DComponent* m_RenderComponent;
		glm::vec3 m_Direction{ -1.f, .0f, .0f };
		const float m_TimeBeforeJump{ 2.f };
		const float m_JumpChance{ .3f };
		float m_JumpTimer{};
	};
}
