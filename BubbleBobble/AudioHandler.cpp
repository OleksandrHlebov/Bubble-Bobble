#include "AudioHandler.h"
#include "MovementComponent.h"
#include "GameEvent.h"
#include "Health.h"
#include <functional>

dae::AudioHandler::AudioHandler(GameObject* owner) : Component(owner)
{
	using namespace std::placeholders;
	GameEvent::Bind("OnJump", std::bind(&AudioHandler::HandleJumpingSound, this, _1));
	GameEvent::Bind("OnHealthChanged", std::bind(&AudioHandler::HandleDamagedSound, this, _1));
}

void dae::AudioHandler::HandleJumpingSound(GameEvent* event)
{
	(void)event;
	m_JumpSFX.Play();
}

void dae::AudioHandler::HandleDamagedSound(GameEvent* event)
{
	Health::OnHealthChanged* healthChanged = static_cast<Health::OnHealthChanged*>(event);
	if (healthChanged->Delta < 0)
		m_Damaged.Play();
}
