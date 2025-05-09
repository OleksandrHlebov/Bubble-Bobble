#include "PlayerState.h"
#include "IdlePlayerState.h"

std::unique_ptr<dae::PlayerState> dae::PlayerState::Update(float)
{
	return std::make_unique<IdlePlayerState>(GetPlayer());
}

void dae::PlayerState::TransitionState(std::unique_ptr<PlayerState>& owningState, std::unique_ptr<PlayerState> newState)
{
	owningState->OnExit();
	owningState = std::move(newState);
	owningState->OnEnter();
}
