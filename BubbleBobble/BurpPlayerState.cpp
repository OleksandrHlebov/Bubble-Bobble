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
	uint32_t playerIndex = GetPlayer()->GetComponent<Controller>()->GetPlayerIndex();

	Animation2DComponent* animComponent = GetPlayer()->GetComponent<Animation2DComponent>();
	animComponent->Play(m_BurpPath[playerIndex], 0, 0, 1);
	auto bubble = GetPlayer()->GetScene()->CreateGameObject();
	auto render = bubble->AddComponent<Render2DComponent>();
	const int framesInTexture{ 7 };
	const std::string path{ "Textures/Bubble_lifecycle.png" };
	render->SetTexture(path);
	Collision2DComponent* collider = bubble->AddComponent<Collision2DComponent>(true);
	collider->SetSize(1.f * render->GetDimensions().x / framesInTexture, 1.f * render->GetDimensions().y);
	collider->EnableDebugDraw();
	auto playerCollision = GetPlayer()->GetComponent<Collision2DComponent>();
	auto movement = GetPlayer()->GetComponent<MovementComponent>();
	const auto [min, max] = playerCollision->GetBounds();
	const glm::vec2 center{ playerCollision->GetCenter() };
	const glm::vec2 direction{ movement->GetForward().x, movement->GetForward().y };
	const float distance{ playerCollision->GetSize().x / 2.f + (direction.x < 0) * collider->GetSize().x };
	const glm::vec3 spawnPos{ center.x + direction.x * distance, min.y, .0f };
	bubble->SetLocalPosition(spawnPos);
	bubble->AddComponent<BubbleComponent>(direction);

	bubble->AddComponent<Animation2DComponent>(.16f)->Play(path, 0, 4, framesInTexture);
	m_CanTransition = false;
}

std::unique_ptr<dae::PlayerState> dae::BurpPlayerState::Update(float deltaTime)
{
	if (m_Timer >= DELAY)
	{
		m_CanTransition = true;
		return std::make_unique<IdlePlayerState>(GetPlayer());
	}
	m_Timer += deltaTime;
	return nullptr;
}

void dae::BurpPlayerState::OnExit()
{
	m_Timer = .0f;
}
