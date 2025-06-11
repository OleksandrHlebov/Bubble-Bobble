#include "WalkingAIState.h"
#include <functional>
#include "GameEvent.h"
#include "GameObject.h"
#include "MovementComponent.h"
#include "Render2DComponent.h"
#include "Collision2DComponent.h"
#include "Animation2DComponent.H"

void dae::WalkingAIState::OnEnter()
{
	using namespace std::placeholders;
	GameEvent::Bind("OnOverlap", std::bind(&WalkingAIState::HandleOverlap, this, _1));

	static const int TOTAL_FRAMES{ 2 };
	Animation2DComponent* animComponent = GetCharacter()->GetComponent<Animation2DComponent>();
	animComponent->Play(GetType().WalkingTexturePath, 0, TOTAL_FRAMES - 1, TOTAL_FRAMES, true);

	m_RenderComponent = GetCharacter()->GetComponent<Render2DComponent>();
	m_MovementComponent = GetCharacter()->GetComponent<MovementComponent>();
	m_MovementComponent->Speed = GetType().Speed;
}

std::unique_ptr<dae::AIState> dae::WalkingAIState::Update(float)
{
	m_MovementComponent->AddMovementInput(m_Direction);
	return nullptr;
}

void dae::WalkingAIState::OnExit()
{

}

void dae::WalkingAIState::HandleOverlap(GameEvent* event)
{
	if (Collision2DComponent::OnOverlap* overlapEvent = static_cast<Collision2DComponent::OnOverlap*>(event))
	{
		// if second collider is static it means that first initiated the sweep
		// and is always first
		// dynamic collisions are being processed differently
		if (!overlapEvent->SecondCollider->IsDynamic() && GetCharacter() == overlapEvent->First)
		{
			if (overlapEvent->Overlap.x < overlapEvent->Overlap.y)
				m_Direction *= -1;
		}
	}
}

