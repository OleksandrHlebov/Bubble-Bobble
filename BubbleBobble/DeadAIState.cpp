#include "DeadAIState.h"
#include "GameObject.h"
#include "Animation2DComponent.h"
#include "TileComponent.h"
#include "AIType.h"

void dae::DeadAIState::OnEnter()
{
	auto animComp = GetCharacter()->GetComponent<Animation2DComponent>();
	auto [path, frames] = GetType().DeadTextureAnim;

	animComp->Play(path, 0, frames - 1, frames, true, m_Loops);
	GameEvent::Bind("OnAnimationFinished", &m_MorphingHandler);
	GameEvent::Bind("OnOverlap", &m_OverlapHandler);
	auto movement = GetCharacter()->GetComponent<MovementComponent>();
	movement->SetEnabled(true);
	movement->Launch(glm::vec3{ .0f, -1.f, .0f }, m_LaunchStrength);
	movement->InAirSlowdownPercent = .0f;
	m_CanTransition = false;
}

std::unique_ptr<dae::AIState> dae::DeadAIState::Update(float deltaTime)
{
	m_MoveCommand.Execute(deltaTime);
	return nullptr;
}

void dae::DeadAIState::OnExit()
{
	GameEvent::UnBind("OnAnimationFinished", &m_MorphingHandler);
	GameEvent::UnBind("OnOverlap", &m_OverlapHandler);
}

void dae::DeadAIState::HandleMorphingIntoFruit(GameEvent* event)
{
	auto animationFinished = static_cast<Animation2DComponent::OnAnimationFinished*>(event);
	if (animationFinished->AnimationComponent->GetOwner() == GetCharacter())
	{
		m_SpawnCommand.Execute(.0f);
		GameEvent::UnBind("OnAnimationFinished", &m_MorphingHandler);
		GameEvent::Dispatch<OnEnemyDeath>();
		GetCharacter()->Delete();
	}
}

void dae::DeadAIState::HandleLanding(GameEvent* event)
{
	if (Collision2DComponent::OnOverlap* overlapEvent = static_cast<Collision2DComponent::OnOverlap*>(event))
	{
		// if second collider is static it means that first initiated the sweep
		// and is always first
		// dynamic collisions are being processed differently
		const bool isResultOfOwnSweep{ !overlapEvent->SecondCollider->IsDynamic() && GetCharacter() == overlapEvent->First };
		if (isResultOfOwnSweep)
		{
			if (auto movement = GetCharacter()->GetComponent<MovementComponent>())
			{
				if (auto tile = overlapEvent->Second->GetComponent<TileComponent>())
				{
					if (!tile->HasTileAbove() && overlapEvent->Overlap.y && overlapEvent->Overlap.x >= overlapEvent->Overlap.y && movement->GetVelocity().y > FLT_EPSILON)
					{
						GetCharacter()->GetComponent<Animation2DComponent>()->Stop();
						GameEvent::UnBind("OnOverlap", &m_OverlapHandler);
					}
				}
			}
		}
	}
}
