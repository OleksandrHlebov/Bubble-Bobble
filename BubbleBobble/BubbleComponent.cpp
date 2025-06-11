#include "BubbleComponent.h"
#include "GameEvent.h"
#include "GameObject.h"
#include <functional>
#include "Collision2DComponent.h"
#include "TileComponent.h"
#include "Brain.h"

void dae::BubbleComponent::Update(float deltaTime)
{
	GetOwner()->GetComponent<Transform>()->Move(glm::vec3{ m_Direction, .0f } * Speed * deltaTime, true);
}

void dae::BubbleComponent::HandleStaticOverlap(GameEvent* event)
{
	if (Collision2DComponent::OnOverlap* overlapEvent = static_cast<Collision2DComponent::OnOverlap*>(event))
	{
		// if second collider is static it means that first initiated the sweep
		// and is always first
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

					m_Direction = glm::vec2{ .0f, -1.f }; // start going up
					using std::placeholders::_1;
					GameEvent::UnBind("OnOverlap", &m_StaticOverlapHandler);
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
			//Collision2DComponent* const selfCollider = (isFirst) ? overlapEvent->FirstCollider : overlapEvent->SecondCollider;
			GameObject* const other = (!isFirst) ? overlapEvent->First : overlapEvent->Second;
			//Collision2DComponent* const otherCollider = (!isFirst) ? overlapEvent->FirstCollider : overlapEvent->SecondCollider;

			if (Brain* brain = other->GetComponent<Brain>())
			{
				brain->TrapInBubble();
				GetOwner()->Delete();
			}
		}
}

void dae::BubbleComponent::Start()
{
	using std::placeholders::_1;
	GameEvent::Bind("OnOverlap", &m_StaticOverlapHandler);
	GameEvent::Bind("OnOverlap", &m_DynamicOverlapHandler);
}

void dae::BubbleComponent::End()
{
	using std::placeholders::_1;
	GameEvent::UnBind("OnOverlap", &m_StaticOverlapHandler);
	GameEvent::UnBind("OnOverlap", &m_DynamicOverlapHandler);
}
