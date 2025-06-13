#include "IdlePlayerState.h"
#include "WalkingPlayerState.h"
#include "GameObject.h"
#include "Render2DComponent.h"
#include "MovementComponent.h"
#include "JumpingPlayerState.h"
#include "Animation2DComponent.H"
#include "Controller.h"

void dae::IdlePlayerState::OnEnter()
{
	Animation2DComponent* animComponent = GetPlayer()->GetComponent<Animation2DComponent>();
	auto [path, frames] = GetType().IdleAnim;
	animComponent->Play(path, 0, frames - 1, frames, true);

	m_MovementComponent = GetPlayer()->GetComponent<MovementComponent>();
}

std::unique_ptr<dae::PlayerState> dae::IdlePlayerState::Update(float)
{
	if (m_MovementComponent->GetVelocity().y < .0f)
		return std::make_unique<JumpingPlayerState>(GetType(), GetPlayer());
	if (abs(m_MovementComponent->GetVelocity().x) > FLT_EPSILON)
		return std::make_unique<WalkingPlayerState>(GetType(), GetPlayer());

	return nullptr;
}

void dae::IdlePlayerState::OnExit()
{
	
}
