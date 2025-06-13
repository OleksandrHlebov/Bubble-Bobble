#include "BurpPlayerState.h"
#include "GameObject.h"
#include "Animation2DComponent.h"
#include "Controller.h"
#include "IdlePlayerState.h"
#include "Scene.h"
#include "Collision2DComponent.h"
#include "MovementComponent.h"
#include "Render2DComponent.h"
#include "BubbleComponent.h"

void dae::BurpPlayerState::OnEnter()
{
	{
		auto [path, frames] = GetType().AttackAnim;
		Animation2DComponent* animComponent = GetPlayer()->GetComponent<Animation2DComponent>();
		animComponent->Play(path, 0, frames - 1, frames);
	}
	GetType().AbilityPtr->ExecuteOn(GetPlayer());

	m_CanTransition = false;
}

std::unique_ptr<dae::PlayerState> dae::BurpPlayerState::Update(float deltaTime)
{
	if (m_Timer >= DELAY)
	{
		m_CanTransition = true;
		return std::make_unique<IdlePlayerState>(GetType(), GetPlayer());
	}
	m_Timer += deltaTime;
	return nullptr;
}

void dae::BurpPlayerState::OnExit()
{
	m_Timer = .0f;
}
