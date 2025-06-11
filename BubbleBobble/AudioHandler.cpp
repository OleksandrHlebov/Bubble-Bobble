#include "AudioHandler.h"
#include "MovementComponent.h"
#include "GameEvent.h"
#include "GameObject.h"
#include "Health.h"
#include <functional>
#include "PlayerController.h"

dae::AudioHandler::AudioHandler(GameObject* owner) : Component(owner)
{
	GameEvent::Bind("OnJump", &m_JumpHandler);
	GameEvent::Bind("OnHealthChanged", &m_DamageHandler);
}

void dae::AudioHandler::HandleJumpingSound(GameEvent* event)
{
	MovementComponent::OnJump* jump = static_cast<MovementComponent::OnJump*>(event);
	if (jump->Object->GetComponent<PlayerController>()) // only players produce sound when jumping
		m_JumpSFX.Play();
}

void dae::AudioHandler::HandleDamagedSound(GameEvent* event)
{
	Health::OnHealthChanged* healthChanged = static_cast<Health::OnHealthChanged*>(event);
	if (healthChanged->Delta < 0)
		m_Damaged.Play();
}

void dae::AudioHandler::End()
{
	GameEvent::UnBind("OnJump", &m_JumpHandler);
	GameEvent::UnBind("OnHealthChanged", &m_DamageHandler);
}
