#include "AudioHandler.h"
#include "MovementComponent.h"
#include "GameEvent.h"
#include <functional>

dae::AudioHandler::AudioHandler(GameObject* owner) : Component(owner)
{
	using namespace std::placeholders;
	GameEvent::Bind("OnJump", std::bind(&AudioHandler::HandleJumpingSound, this, _1));
}

void dae::AudioHandler::HandleJumpingSound(GameEvent* event)
{
	(void)event;
	m_JumpSFX.Play();
}
