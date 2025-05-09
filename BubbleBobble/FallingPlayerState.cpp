#include "FallingPlayerState.h"
#include "GameObject.h"
#include "Animation2DComponent.h"
#include "MovementComponent.h"
#include "Render2DComponent.h"
#include "IdlePlayerState.h"
#include "Controller.h"

void dae::FallingPlayerState::OnEnter()
{
	static const int TOTAL_FRAMES{ 4 };
	uint32_t playerIndex = GetPlayer()->GetComponent<Controller>()->GetPlayerIndex();

	Animation2DComponent* animComponent = GetPlayer()->GetComponent<Animation2DComponent>();
	animComponent->Play(m_JumpingPath[playerIndex], 2, TOTAL_FRAMES - 1, TOTAL_FRAMES, false);

	m_MovementComponent = GetPlayer()->GetComponent<MovementComponent>();
	m_RenderComponent = GetPlayer()->GetComponent<Render2DComponent>();
}

std::unique_ptr<dae::PlayerState> dae::FallingPlayerState::Update(float)
{
	if (m_MovementComponent->GetVelocity().y < FLT_EPSILON)
		return std::make_unique<IdlePlayerState>(GetPlayer());
	if (abs(m_MovementComponent->GetVelocity().x) > FLT_EPSILON)
		m_RenderComponent->Flip(m_MovementComponent->GetVelocity().x < 0);
	return nullptr;
}

void dae::FallingPlayerState::OnExit()
{
}
