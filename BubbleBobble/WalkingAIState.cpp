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
	using namespace std::placeholders;
	GameEvent::Bind("OnOverlap", std::bind(&WalkingAIState::HandleOverlap, this, _1));

	static const int TOTAL_FRAMES{ 2 };
	Animation2DComponent* animComponent = GetCharacter()->GetComponent<Animation2DComponent>();
	animComponent->Play(GetType().WalkingTexturePath, 0, TOTAL_FRAMES - 1, TOTAL_FRAMES, true);

	m_RenderComponent = GetCharacter()->GetComponent<Render2DComponent>();
	m_MovementComponent = GetCharacter()->GetComponent<MovementComponent>();
	m_MovementComponent->Speed = GetType().Speed;
}

std::unique_ptr<dae::AIState> dae::WalkingAIState::Update(float)
{
	if (m_MovementComponent->GetVelocity().y < FLT_EPSILON)
		m_MovementComponent->AddMovementInput(m_Direction);
	return nullptr;
}

void dae::WalkingAIState::OnExit()
{
	using namespace std::placeholders;
	GameEvent::UnBind("OnOverlap", std::bind(&WalkingAIState::HandleOverlap, this, _1));
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
			if (overlapEvent->Overlap.x < overlapEvent->Overlap.y)
			{
				Scene* scene = GetCharacter()->GetScene();
				const glm::vec2 center = overlapEvent->FirstCollider->GetCenter();
				// check 2 pixels ahead of character
				const float rayLength = overlapEvent->FirstCollider->GetSize().x / 2.f + 2;
				if (auto [collider, intersection] = scene->TraceSegment(center, m_Direction, rayLength, false, true); collider)
				{
					m_Direction *= -1;
					m_RenderComponent->Flip(m_Direction.x > 0);
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

			if (other->GetComponent<PlayerController>())
				other->GetComponent<Health>()->ApplyHealth(-1);
		}
	}
}

