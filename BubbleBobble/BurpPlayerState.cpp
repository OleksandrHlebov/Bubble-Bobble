#include "BurpPlayerState.h"
#include "GameObject.h"
#include "Animation2DComponent.h"
#include "Controller.h"
#include "IdlePlayerState.h"

void dae::BurpPlayerState::OnEnter()
{
	uint32_t playerIndex = GetPlayer()->GetComponent<Controller>()->GetPlayerIndex();

	Animation2DComponent* animComponent = GetPlayer()->GetComponent<Animation2DComponent>();
	animComponent->Play(m_BurpPath[playerIndex], 0, 0, 1);
}

std::unique_ptr<dae::PlayerState> dae::BurpPlayerState::Update(float deltaTime)
{
	if (m_Timer >= DELAY)
		return std::make_unique<IdlePlayerState>(GetPlayer());
	m_Timer += deltaTime;
	return nullptr;
}

void dae::BurpPlayerState::OnExit()
{
	m_Timer = .0f;
}
