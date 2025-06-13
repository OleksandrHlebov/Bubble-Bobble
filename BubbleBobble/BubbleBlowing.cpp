#include "BubbleBlowing.h"
#include "GameObject.h"
#include "Scene.h"
#include "Render2DComponent.h"
#include "Collision2DComponent.h"
#include "MovementComponent.h"
#include "BubbleComponent.h"
#include "Animation2DComponent.H"
#include "PlayerController.h"

void dae::BubbleBlowing::ExecuteOn(GameObject* gameObject)
{
	const uint32_t playerIndex = gameObject->GetComponent<PlayerController>()->GetPlayerIndex() % static_cast<uint32_t>(std::size(m_BubbleAnim));
	auto bubble = gameObject->GetScene()->CreateGameObject();
	auto render = bubble->AddComponent<Render2DComponent>();
	auto [path, frames] = m_BubbleAnim[playerIndex];
	render->SetTexture(path);
	Collision2DComponent* collider = bubble->AddComponent<Collision2DComponent>(true);
	collider->SetSize(1.f * render->GetDimensions().x / frames, 1.f * render->GetDimensions().y);
	collider->EnableDebugDraw();
	auto playerCollision = gameObject->GetComponent<Collision2DComponent>();
	auto movement = gameObject->GetComponent<MovementComponent>();
	const auto [min, max] = playerCollision->GetBounds();
	const glm::vec2 center{ playerCollision->GetCenter() };
	const glm::vec2 direction{ movement->GetForward().x, movement->GetForward().y };
	const float distance{ playerCollision->GetSize().x / 2.f + (direction.x < 0) * collider->GetSize().x };
	const glm::vec3 spawnPos{ center.x + direction.x * distance, min.y, .0f };
	bubble->SetLocalPosition(spawnPos);
	bubble->AddComponent<BubbleComponent>(direction);

	bubble->AddComponent<Animation2DComponent>(.16f)->Play(path, 0, 4, frames);
}
