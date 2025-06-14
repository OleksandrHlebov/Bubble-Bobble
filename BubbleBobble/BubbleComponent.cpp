#include "BubbleComponent.h"
#include "GameEvent.h"
#include "GameObject.h"
#include <functional>
#include "Collision2DComponent.h"
#include "TileComponent.h"
#include "Brain.h"
#include "Animation2DComponent.H"
#include "Render2DComponent.h"
#include <cassert>
#include "PlayerController.h"
#include "Health.h"

void dae::BubbleComponent::Update(float deltaTime)
{
	if (!m_IsAboutToPop)
	{
		const float modifier{ Speed * deltaTime * (GetOwner()->GetWorldPosition().y > m_MinY) };
		GetOwner()->GetComponent<Transform>()->Move(glm::vec3{ m_Direction, .0f } *modifier, true);
	}
	if (m_LifeTimer >= m_Lifetime)
	{
		Pop();
	}
	m_LifeTimer += deltaTime * (!m_IsAboutToPop);
}

void dae::BubbleComponent::HandleStaticOverlap(GameEvent* event)
{
	if (Collision2DComponent::OnOverlap* overlapEvent = static_cast<Collision2DComponent::OnOverlap*>(event))
	{
		// if second collider is static it means that first initiated the sweep
		// and this object is always first
		// dynamic collisions are being processed differently
		if (!overlapEvent->SecondCollider->IsDynamic() && GetOwner() == overlapEvent->First)
		{
			Collision2DComponent* selfCollider = overlapEvent->FirstCollider;
			Collision2DComponent* otherCollider = overlapEvent->SecondCollider;
			auto [selfMin, selfMax] = selfCollider->GetBounds();
			auto [otherMin, otherMax] = otherCollider->GetBounds();
			glm::vec2 resolve{};

			if (overlapEvent->Overlap.x)
			{
				TileComponent* tileComp = overlapEvent->SecondCollider->GetOwner()->GetComponent<TileComponent>();
				if (tileComp->HasTileAbove())
				{
					if (overlapEvent->Normal.x > 0)
						resolve.x = overlapEvent->Overlap.x;
					else
						resolve.x = -overlapEvent->Overlap.x;

					StartGoingUp();
				}
			}

			GetOwner()->GetComponent<Transform>()->Move({ resolve, .0f });
		}
	}
}

void dae::BubbleComponent::HandleDynamicOverlap(GameEvent* event)
{
	if (Collision2DComponent::OnOverlap* overlapEvent = static_cast<Collision2DComponent::OnOverlap*>(event))
		// collided with player or other npc
		if (overlapEvent->SecondCollider->IsDynamic() && (overlapEvent->First == GetOwner() || overlapEvent->Second == GetOwner()))
		{
			const bool isFirst{ overlapEvent->First == GetOwner() };
			//GameObject* const self = (isFirst) ? overlapEvent->First : overlapEvent->Second;
			Collision2DComponent* const selfCollider = (isFirst) ? overlapEvent->FirstCollider : overlapEvent->SecondCollider;
			GameObject* const other = (!isFirst) ? overlapEvent->First : overlapEvent->Second;
			Collision2DComponent* const otherCollider = (!isFirst) ? overlapEvent->FirstCollider : overlapEvent->SecondCollider;

			if (Brain* brain = other->GetComponent<Brain>())
			{
				if (brain->TrapInBubble())
					GetOwner()->Delete();
			}
			if (PlayerController* controller = other->GetComponent<PlayerController>())
			{
				if (controller->IsHostile())
				{
					other->GetComponent<Health>()->ApplyHealth(-1);
					Pop();
				}
			}
			if (other->GetComponent<BubbleComponent>())
			{
				auto [selfMin, selfMax] = selfCollider->GetBounds();
				auto [otherMin, otherMax] = otherCollider->GetBounds();
				glm::vec2 resolve{};
				const float normalDirection{ (isFirst) ? 1.f : -1.f };
				if (overlapEvent->Overlap.x && overlapEvent->Overlap.x < overlapEvent->Overlap.y)
				{
					if (normalDirection * overlapEvent->Normal.x > 0)
						resolve.x = overlapEvent->Overlap.x;
					else
						resolve.x = -overlapEvent->Overlap.x;
				}
				else
				{
					if (normalDirection * overlapEvent->Normal.y > 0)
						resolve.y = overlapEvent->Overlap.y;
					else
						resolve.y = -overlapEvent->Overlap.y;
				}

				GetOwner()->GetComponent<Transform>()->Move({ resolve, .0f });
			}
		}
}

void dae::BubbleComponent::HandleAnimationFinished(GameEvent* event)
{
	Animation2DComponent::OnAnimationFinished* animFinished = static_cast<Animation2DComponent::OnAnimationFinished*>(event);
	if (animFinished->AnimationComponent->GetOwner() == GetOwner())
	{
		StartGoingUp();
	}
}

void dae::BubbleComponent::HandleEndOfLifecycle(GameEvent* event)
{
	Animation2DComponent::OnAnimationFinished* animFinished = static_cast<Animation2DComponent::OnAnimationFinished*>(event);
	if (animFinished->AnimationComponent->GetOwner() == GetOwner())
	{
		GameEvent::UnBind("OnAnimationFinished", &m_DestructionHandler);
		GetOwner()->Delete();
	}
}

void dae::BubbleComponent::Start()
{
	GameEvent::Bind("OnOverlap", &m_StaticOverlapHandler);
	GameEvent::Bind("OnOverlap", &m_DynamicOverlapHandler);
	GameEvent::Bind("OnAnimationFinished", &m_AnimationFinishedHandler);
}

void dae::BubbleComponent::End()
{
	GameEvent::UnBind("OnOverlap", &m_StaticOverlapHandler);
	GameEvent::UnBind("OnOverlap", &m_DynamicOverlapHandler);
	GameEvent::UnBind("OnAnimationFinished", &m_AnimationFinishedHandler);
	GameEvent::UnBind("OnAnimationFinished", &m_DestructionHandler);
}

void dae::BubbleComponent::Pop()
{
	Animation2DComponent* animComp = GetOwner()->GetComponent<Animation2DComponent>();
	assert(animComp->GetTotalFrames() == 7);
	GetOwner()->GetComponent<Collision2DComponent>()->Delete();
	animComp->PlayCurrent(5, 6, animComp->GetTotalFrames(), false);
	GameEvent::Bind("OnAnimationFinished", &m_DestructionHandler);
	m_LifeTimer -= m_Lifetime;
	m_IsAboutToPop = true;
}

void dae::BubbleComponent::StartGoingUp()
{
	m_Direction = glm::vec2{ .0f, -1.f }; // start going up
	GameEvent::UnBind("OnOverlap", &m_StaticOverlapHandler);
	GameEvent::UnBind("OnAnimationFinished", &m_AnimationFinishedHandler);
	Animation2DComponent* animComp = GetOwner()->GetComponent<Animation2DComponent>();
	assert(animComp->GetTotalFrames() == 7);
	animComp->PlayCurrent(3, 4, animComp->GetTotalFrames(), true);
}
