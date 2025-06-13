#include "FallingPlayerState.h"
#include "GameObject.h"
#include "Animation2DComponent.h"
#include "MovementComponent.h"
#include "Render2DComponent.h"
#include "IdlePlayerState.h"
#include "Controller.h"

void dae::FallingPlayerState::OnEnter()
{
	auto [path, frames] = GetType().FallingAnim;

	Animation2DComponent* animComponent = GetPlayer()->GetComponent<Animation2DComponent>();
	animComponent->Play(path, 0, frames - 1, frames, true);

	m_MovementComponent = GetPlayer()->GetComponent<MovementComponent>();
	m_RenderComponent = GetPlayer()->GetComponent<Render2DComponent>();
}

std::unique_ptr<dae::PlayerState> dae::FallingPlayerState::Update(float)
{
	if (m_MovementComponent->GetVelocity().y < FLT_EPSILON)
		return std::make_unique<IdlePlayerState>(GetType(), GetPlayer());
	if (abs(m_MovementComponent->GetVelocity().x) > FLT_EPSILON)
		m_RenderComponent->Flip(m_MovementComponent->GetVelocity().x < 0);
	return nullptr;
}

void dae::FallingPlayerState::OnExit()
{
}
