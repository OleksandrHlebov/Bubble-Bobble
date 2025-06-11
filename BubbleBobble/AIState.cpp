#include "AIState.h"
#include "WalkingAIState.h"

std::unique_ptr<dae::AIState> dae::AIState::Update(float)
{
	return std::make_unique<WalkingAIState>(GetCharacter(), GetType());
}

void dae::AIState::TransitionState(std::unique_ptr<AIState>& owningState, std::unique_ptr<AIState> newState)
{
	owningState->OnExit();
	owningState = std::move(newState);
	owningState->OnEnter();
}
