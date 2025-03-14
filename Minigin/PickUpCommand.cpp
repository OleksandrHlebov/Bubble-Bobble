#include "PickUpCommand.h"
#include "PickUpComponent.h"
#include "GameObject.h"

void dae::PickUpCommand::Execute()
{
	if (PickUpComponent* comp = GetGameObject()->GetComponent<PickUpComponent>())
	{
		comp->PickUp();
	}
}
