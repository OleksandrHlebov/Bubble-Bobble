#include "BurpCommand.h"
#include "BubbleComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "Collision2DComponent.h"
#include "MovementComponent.h"
#include "Animation2DComponent.H"
#include "Render2DComponent.h"

void dae::BurpCommand::Execute(float)
{
	// spawn bubble
	GameEvent::Dispatch<OnBurp>(GetGameObject());
}

