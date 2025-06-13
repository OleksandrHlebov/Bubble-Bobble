#include "TrappedAIState.h"
#include "WalkingAIState.h"
#include "GameEvent.h"
#include "Collision2DComponent.h"
#include "GameObject.h"
#include "PlayerController.h"
#include "MovementComponent.h"
#include "Animation2DComponent.H"
#include "DeadAIState.h"

void dae::TrappedAIState::OnEnter()
{
	auto movement = GetCharacter()->GetComponent<MovementComponent>();
	movement->SetEnabled(false);
	m_FloatingSpeed = movement->Speed - movement->Speed * movement->InAirSlowdownPercent;
	GameEvent::Bind("OnOverlap", &m_OverlapHandler);
	auto animComp = GetCharacter()->GetComponent<Animation2DComponent>();
	auto [path, frames] = GetType().TrappedTextureAnim;
	animComp->Play(path, 0, frames - 1, frames, true);
	m_CanTransition = false;
}

std::unique_ptr<dae::AIState> dae::TrappedAIState::Update(float deltaTime)
{
	if (m_Died)
	{
		m_CanTransition = true;
		return std::make_unique<DeadAIState>(GetCharacter(), GetType());
	}
	if (m_EscapeTimer >= m_TimeToEscape)
	{
		m_CanTransition = true;
		return std::make_unique<WalkingAIState>(GetCharacter(), GetType());
	}
	auto transform = GetCharacter()->GetComponent<Transform>();
	if (transform->GetWorldPosition().y > m_MinY)
		transform->Move({ .0f, -m_FloatingSpeed * deltaTime, .0f }, true);
	m_EscapeTimer += deltaTime;
	return nullptr;
}

void dae::TrappedAIState::OnExit()
{
	GameEvent::UnBind("OnOverlap", &m_OverlapHandler);
}

void dae::TrappedAIState::HandleOverlap(GameEvent* event)
{
	auto overlapEvent = static_cast<Collision2DComponent::OnOverlap*>(event);
	if (overlapEvent->SecondCollider->IsDynamic() && (overlapEvent->First == GetCharacter() || overlapEvent->Second == GetCharacter()))
	{
		const bool isFirst{ overlapEvent->First == GetCharacter() };
		GameObject* other = (isFirst) ? overlapEvent->Second : overlapEvent->First;
		if (other->GetComponent<PlayerController>())
		{
			m_Died = true;
		}
	}
}
