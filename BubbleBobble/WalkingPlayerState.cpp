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
	static const int TOTAL_FRAMES{ 4 };
	uint32_t playerIndex = GetPlayer()->GetComponent<Controller>()->GetPlayerIndex();

	Animation2DComponent* animComponent = GetPlayer()->GetComponent<Animation2DComponent>();
	animComponent->Play(m_WalkingPath[playerIndex], 0, TOTAL_FRAMES - 1, TOTAL_FRAMES, true);

	m_MovementComponent = GetPlayer()->GetComponent<MovementComponent>();
	m_RenderComponent = GetPlayer()->GetComponent<Render2DComponent>();
}

std::unique_ptr<dae::PlayerState> dae::WalkingPlayerState::Update(float)
{
	if (m_MovementComponent->GetVelocity().y < 0)
		return std::make_unique<JumpingPlayerState>(GetPlayer());
	if (m_MovementComponent->GetVelocity().y > 0)
		return std::make_unique<FallingPlayerState>(GetPlayer());
	if (abs(m_MovementComponent->GetVelocity().x) < FLT_EPSILON)
		return std::make_unique<IdlePlayerState>(GetPlayer());
	m_RenderComponent->Flip(m_MovementComponent->GetVelocity().x < 0);
	return nullptr;
}

void dae::WalkingPlayerState::OnExit()
{
}
