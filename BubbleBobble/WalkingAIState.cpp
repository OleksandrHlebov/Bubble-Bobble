#include "WalkingAIState.h"
#include <functional>
#include "GameEvent.h"
#include "GameObject.h"
#include "MovementComponent.h"
#include "Render2DComponent.h"
#include "Collision2DComponent.h"
#include "Animation2DComponent.H"
#include "Scene.h"
#include "Health.h"
#include "PlayerController.h"

void dae::WalkingAIState::OnEnter()
{
	GameEvent::Bind("OnOverlap", &m_OverlapHandler);

	Animation2DComponent* animComponent = GetCharacter()->GetComponent<Animation2DComponent>();
	auto [path, frames] = GetType().WalkingTextureAnim;
	animComponent->Play(path, 0, frames - 1, frames, true);

	m_RenderComponent = GetCharacter()->GetComponent<Render2DComponent>();
	m_MovementComponent = GetCharacter()->GetComponent<MovementComponent>();
	m_MovementComponent->Speed = GetType().Speed;
	m_MovementComponent->SetEnabled(true);
	m_RenderComponent->Flip(m_Direction.x < 0);
}

std::unique_ptr<dae::AIState> dae::WalkingAIState::Update(float deltaTime)
{
	if (m_MovementComponent->GetVelocity().y < FLT_EPSILON)
		m_MoveCommand.Execute(deltaTime);

	if (m_JumpTimer >= m_TimeBeforeJump)
	{
		m_JumpTimer -= m_TimeBeforeJump;
		int randomNumber{ rand() % 101 };
		if (randomNumber / 100.f > m_JumpChance)
			m_JumpCommand.Execute(deltaTime);
	}

	if (m_AbilityTimer >= m_TimeBeforeAbility)
	{
		m_AbilityTimer -= m_TimeBeforeAbility;
		int randomNumber{ rand() % 101 };
		if (randomNumber / 100.f > m_AbilityChance)
			GetType().AbilityPtr->ExecuteOn(GetCharacter());
	}

	m_JumpTimer += deltaTime;
	m_AbilityTimer += deltaTime;
	return nullptr;
}

void dae::WalkingAIState::OnExit()
{
	GameEvent::UnBind("OnOverlap", &m_OverlapHandler);
}

void dae::WalkingAIState::HandleOverlap(GameEvent* event)
{
	if (Collision2DComponent::OnOverlap* overlapEvent = static_cast<Collision2DComponent::OnOverlap*>(event))
	{
		// if second collider is static it means that first initiated the sweep
		// and is always first
		// dynamic collisions are being processed differently
		if (!overlapEvent->SecondCollider->IsDynamic() && GetCharacter() == overlapEvent->First)
		{
			// possible horizontal collision
			if (overlapEvent->Overlap.x < overlapEvent->Overlap.y && abs(m_MovementComponent->GetVelocity().y) < FLT_EPSILON)
			{
				Scene* scene = GetCharacter()->GetScene();
				const glm::vec2 center = overlapEvent->FirstCollider->GetCenter();
				// check 2 pixels ahead of character
				const float rayLength = overlapEvent->FirstCollider->GetSize().x / 2.f + 2;
				if (auto [collider, intersection] = scene->TraceSegment(center, m_Direction, rayLength, false, true); collider)
				{
					m_MoveCommand.SetDirection(m_Direction *= -1);
					m_RenderComponent->Flip(m_Direction.x < 0);
				}
			}
		}
		// collided with player or other npc
		if (overlapEvent->SecondCollider->IsDynamic() && (overlapEvent->First == GetCharacter() || overlapEvent->Second == GetCharacter()))
		{
			const bool isFirst{ overlapEvent->First == GetCharacter() };
			//GameObject* const self = (isFirst) ? overlapEvent->First : overlapEvent->Second;
			//Collision2DComponent* const selfCollider = (isFirst) ? overlapEvent->FirstCollider : overlapEvent->SecondCollider;
			GameObject* const other = (!isFirst) ? overlapEvent->First : overlapEvent->Second;
			//Collision2DComponent* const otherCollider = (!isFirst) ? overlapEvent->FirstCollider : overlapEvent->SecondCollider;

			if (PlayerController* controller = other->GetComponent<PlayerController>())
				other->GetComponent<Health>()->ApplyHealth(-1);
		}
	}
}

