#include "PelletComponent.h"
#include "GameEvent.h"
#include "Score.h"

void dae::PelletComponent::PickUp(GameObject* instigator)
{
	GameEvent::Dispatch<ScoreChange>(instigator, m_Value);
}
