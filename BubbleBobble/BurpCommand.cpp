#include "BurpCommand.h"

void dae::BurpCommand::Execute()
{
	// spawn bubble
	//auto bubble = GetGameObject()->GetScene()->CreateGameObject();
	//bubble->AddComponent<BubbleComponent>();
	//bubble->AddComponent<Collision2DComponent>();
	GameEvent::Dispatch<OnBurp>(GetGameObject());
}

