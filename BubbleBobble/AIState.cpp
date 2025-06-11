#include "AIState.h"
#include "WalkingAIState.h"
#include "Helpers.h"

std::unique_ptr<dae::AIState> dae::AIState::Update(float)
{
	return std::make_unique<WalkingAIState>(GetCharacter(), GetType());
}
