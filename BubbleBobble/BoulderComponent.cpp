#include "BoulderComponent.h"
#include "Collision2DComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "PlayerController.h"
#include "Health.h"
#include "Animation2DComponent.H"
#include "Render2DComponent.h"

void dae::BoulderComponent::Start()
{
	GameEvent::Bind("OnOverlap", &m_OverlapHandler);
	GameEvent::Bind("OnAnimationFinished", &m_EndOfLifeHandler);
	GetOwner()->GetComponent<Render2DComponent>()->Flip(m_Direction.x > 0);
}

void dae::BoulderComponent::Update(float deltaTime)
{
	if (!m_IsBroken)
		GetOwner()->GetComponent<Transform>()->Move(m_Direction * m_Speed * deltaTime, true);
}

void dae::BoulderComponent::End()
{
	GameEvent::UnBind("OnOverlap", &m_OverlapHandler);
	GameEvent::UnBind("OnAnimationFinished", &m_EndOfLifeHandler);
}

void dae::BoulderComponent::Break()
{
	auto animComp = GetOwner()->GetComponent<Animation2DComponent>();
	animComp->PlayCurrent(4, 5, animComp->GetTotalFrames());
	m_IsBroken = true;
	GameEvent::UnBind("OnOverlap", &m_OverlapHandler);
}

void dae::BoulderComponent::HandleOverlap(GameEvent* event)
{
	auto overlapEvent = static_cast<Collision2DComponent::OnOverlap*>(event);
	// if second collider is static it means that first initiated the sweep
	// and is always first
	// dynamic collisions are being processed differently
	if (!overlapEvent->SecondCollider->IsDynamic() && GetOwner() == overlapEvent->First)
	{
		// possible horizontal collision
		if (overlapEvent->Overlap.x < overlapEvent->Overlap.y)
		{
			Scene* scene = GetOwner()->GetScene();
			const glm::vec2 center = overlapEvent->FirstCollider->GetCenter();
			// check 2 pixels ahead of boulder
			const float rayLength = overlapEvent->FirstCollider->GetSize().x / 2.f + 2;
			if (auto [collider, intersection] = scene->TraceSegment(center, m_Direction, rayLength, false, true); collider)
			{
				Break();
			}
		}
	}
	// collided with player or other npc
	if (overlapEvent->SecondCollider->IsDynamic() && (overlapEvent->First == GetOwner() || overlapEvent->Second == GetOwner()))
	{
		const bool isFirst{ overlapEvent->First == GetOwner() };
		//GameObject* const self = (isFirst) ? overlapEvent->First : overlapEvent->Second;
		//Collision2DComponent* const selfCollider = (isFirst) ? overlapEvent->FirstCollider : overlapEvent->SecondCollider;
		GameObject* const other = (!isFirst) ? overlapEvent->First : overlapEvent->Second;
		//Collision2DComponent* const otherCollider = (!isFirst) ? overlapEvent->FirstCollider : overlapEvent->SecondCollider;

		if (PlayerController* controller = other->GetComponent<PlayerController>(); controller && other != m_Creator)
		{
			other->GetComponent<Health>()->ApplyHealth(-1);
			Break();
		}
	}
}

void dae::BoulderComponent::HandleEndOfLife(GameEvent* event)
{
	auto animFinished = static_cast<Animation2DComponent::OnAnimationFinished*>(event);
	if (animFinished->AnimationComponent->GetOwner() == GetOwner())
	{
		if (!m_IsBroken)
		{
			Break();
		}
		else 
			GetOwner()->Delete();
	}
}
