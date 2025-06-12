#include "JumpingPlayerState.h"
#include "GameObject.h"
#include "Animation2DComponent.H"
#include "MovementComponent.h"
#include "Render2DComponent.h"
#include "FallingPlayerState.h"
#include "Controller.h"

void dae::JumpingPlayerState::OnEnter()
{
	static const int TOTAL_FRAMES{ 4 };
	uint32_t playerIndex = GetPlayer()->GetComponent<Controller>()->GetPlayerIndex();

	Animation2DComponent* animComponent = GetPlayer()->GetComponent<Animation2DComponent>();
	animComponent->Play(m_JumpingPath[playerIndex], 0, 0, TOTAL_FRAMES, true);

	m_MovementComponent = GetPlayer()->GetComponent<MovementComponent>();
	m_RenderComponent = GetPlayer()->GetComponent<Render2DComponent>();
}

std::unique_ptr<dae::PlayerState> dae::JumpingPlayerState::Update(float)
{
	if (m_MovementComponent->GetVelocity().y >= .0f)
		return std::make_unique<FallingPlayerState>(GetPlayer());
	if (abs(m_MovementComponent->GetVelocity().x) > FLT_EPSILON)
		m_RenderComponent->Flip(m_MovementComponent->GetVelocity().x < 0);
	return nullptr;
}

void dae::JumpingPlayerState::OnExit()
{
}
