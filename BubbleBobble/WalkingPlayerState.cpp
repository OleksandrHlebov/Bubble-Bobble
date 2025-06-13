#include "WalkingPlayerState.h"
#include "Render2DComponent.h"
#include "MovementComponent.h"
#include "GameObject.h"
#include "Animation2DComponent.H"
#include "IdlePlayerState.h"
#include "FallingPlayerState.h"
#include "JumpingPlayerState.h"
#include "Controller.h"

void dae::WalkingPlayerState::OnEnter()
{
	auto [path, frames] = GetType().WalkingAnim;
	Animation2DComponent* animComponent = GetPlayer()->GetComponent<Animation2DComponent>();
	animComponent->Play(path, 0, frames - 1, frames, true);

	m_MovementComponent = GetPlayer()->GetComponent<MovementComponent>();
	m_RenderComponent = GetPlayer()->GetComponent<Render2DComponent>();
}

std::unique_ptr<dae::PlayerState> dae::WalkingPlayerState::Update(float)
{
	if (m_MovementComponent->GetVelocity().y < 0)
		return std::make_unique<JumpingPlayerState>(GetType(), GetPlayer());
	if (m_MovementComponent->GetVelocity().y > 0)
		return std::make_unique<FallingPlayerState>(GetType(), GetPlayer());
	if (abs(m_MovementComponent->GetVelocity().x) < FLT_EPSILON)
		return std::make_unique<IdlePlayerState>(GetType(), GetPlayer());
	m_RenderComponent->Flip(m_MovementComponent->GetVelocity().x < 0);
	return nullptr;
}

void dae::WalkingPlayerState::OnExit()
{
}
