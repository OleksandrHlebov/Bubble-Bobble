#include "DyingPlayerState.h"
#include "IdlePlayerState.h"
#include "GameObject.h"
#include "Animation2DComponent.H"
#include "Health.h"
#include "Controller.h"

void dae::DyingPlayerState::OnEnter()
{
	auto [path, frames] = GetType().DyingAnim;
	m_AnimComponent = GetPlayer()->GetComponent<Animation2DComponent>();
	m_AnimComponent->Play(path, 0, frames - 1, frames);
	m_CanTransition = false;
}

std::unique_ptr<dae::PlayerState> dae::DyingPlayerState::Update(float)
{
	if (!m_AnimComponent->IsPlaying())
	{
		m_CanTransition = true;
		GetPlayer()->GetComponent<Health>()->ResetImmunity();
		return std::make_unique<IdlePlayerState>(GetType(), GetPlayer());
	}
	return nullptr;
}

void dae::DyingPlayerState::OnExit()
{
}
