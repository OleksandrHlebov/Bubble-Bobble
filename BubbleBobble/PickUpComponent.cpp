#include "PickUpComponent.h"
#include "Score.h"


void dae::PickUpComponent::PickUp()
{
	// TODO: some checks for pellets in radius
	GameEvent::Dispatch<ScoreChange>(GetOwner(), 100);
}
