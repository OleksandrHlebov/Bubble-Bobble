#include "DeadAIState.h"
#include "GameObject.h"
#include "Animation2DComponent.h"

void dae::DeadAIState::OnEnter()
{
	auto animComp = GetCharacter()->GetComponent<Animation2DComponent>();
	auto [path, frames] = GetType().DeadTexturePath;

	const uint32_t loops = static_cast<uint32_t>(rand()) % (m_MaxLoops - m_MinLoops + 1) + m_MinLoops;
	animComp->Play(path, 0, frames - 1, frames, true, loops);
	GameEvent::Bind("OnAnimationFinished", &m_MorphingHandler);
	auto movement = GetCharacter()->GetComponent<MovementComponent>();
	movement->SetEnabled(true);
	movement->Launch(glm::vec3{ .0f, -1.f, .0f }, m_LaunchStrength);
	movement->InAirSlowdownPercent = .0f;
	//GetCharacter()->GetComponent<Collision2DComponent>()->SetEnabled(false);
}

std::unique_ptr<dae::AIState> dae::DeadAIState::Update(float deltaTime)
{
	m_MoveCommand.Execute(deltaTime);
	return nullptr;
}

void dae::DeadAIState::OnExit()
{
	GameEvent::UnBind("OnAnimationFinished", &m_MorphingHandler);
}

void dae::DeadAIState::HandleMorphingIntoFruit(GameEvent* event)
{
	auto animationFinished = static_cast<Animation2DComponent::OnAnimationFinished*>(event);
	if (animationFinished->AnimationComponent->GetOwner() == GetCharacter())
	{
		// spawn fruit
		// ...
		GameEvent::UnBind("OnAnimationFinished", &m_MorphingHandler);
		GetCharacter()->Delete();
	}
}
