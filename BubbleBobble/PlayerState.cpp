#include "PlayerState.h"
#include "IdlePlayerState.h"
#include "Helpers.h"

std::unique_ptr<dae::PlayerState> dae::PlayerState::Update(float)
{
	return std::make_unique<IdlePlayerState>(GetType(), GetPlayer());
}
