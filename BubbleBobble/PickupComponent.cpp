#include "PickupComponent.h"
#include "Collision2DComponent.h"
#include "GameObject.h"
#include "PlayerController.h"

void dae::PickupComponent::Start()
{
	GameEvent::Bind("OnOverlap", &m_OverlapHandler);
}

void dae::PickupComponent::End()
{
	GameEvent::UnBind("OnOverlap", &m_OverlapHandler);
}

void dae::PickupComponent::HandleOverlap(GameEvent* event)
{
	auto overlapEvent = static_cast<Collision2DComponent::OnOverlap*>(event);
	if (overlapEvent->First->GetComponent<PlayerController>() && overlapEvent->Second == GetOwner())
	{
		GameEvent::Dispatch<OnPickup>(overlapEvent->First, m_Value);
		GameEvent::UnBind("OnOverlap", &m_OverlapHandler);
		GetOwner()->Delete();
	}
}
