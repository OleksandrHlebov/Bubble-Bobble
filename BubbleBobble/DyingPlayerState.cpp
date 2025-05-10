#include "DyingPlayerState.h"
#include "IdlePlayerState.h"
#include "GameObject.h"
#include "Animation2DComponent.H"
#include "Health.h"
#include "Controller.h"

void dae::DyingPlayerState::OnEnter()
{
	static const uint32_t TOTAL_FRAMES{ 6 };
	uint32_t playerIndex = GetPlayer()->GetComponent<Controller>()->GetPlayerIndex();

	m_AnimComponent = GetPlayer()->GetComponent<Animation2DComponent>();
	m_AnimComponent->Play(m_DyingPath[playerIndex], 0, 5, TOTAL_FRAMES);
}

std::unique_ptr<dae::PlayerState> dae::DyingPlayerState::Update(float)
{
	if (!m_AnimComponent->IsPlaying())
	{
		GetPlayer()->GetComponent<Health>()->ResetHP();
		return std::make_unique<IdlePlayerState>(GetPlayer());
	}
	return nullptr;
}

void dae::DyingPlayerState::OnExit()
{
}
