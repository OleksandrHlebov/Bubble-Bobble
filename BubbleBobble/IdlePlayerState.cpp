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
	static const int TOTAL_FRAMES{ 4 };
	uint32_t playerIndex = GetPlayer()->GetComponent<Controller>()->GetPlayerIndex();

	Animation2DComponent* animComponent = GetPlayer()->GetComponent<Animation2DComponent>();
	animComponent->Play(m_IdlePath[playerIndex], 0, 0, TOTAL_FRAMES, true);

	m_MovementComponent = GetPlayer()->GetComponent<MovementComponent>();
}

std::unique_ptr<dae::PlayerState> dae::IdlePlayerState::Update(float)
{
	if (m_MovementComponent->GetVelocity().y < .0f)
		return std::make_unique<JumpingPlayerState>(GetPlayer());
	if (abs(m_MovementComponent->GetVelocity().x) > FLT_EPSILON)
		return std::make_unique<WalkingPlayerState>(GetPlayer());

	return nullptr;
}

void dae::IdlePlayerState::OnExit()
{
	
}
