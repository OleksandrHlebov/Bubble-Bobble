#include "SpawnFruitCommand.h"
#include "GameObject.h"
#include "Scene.h"
#include "PickupComponent.h"
#include "Collision2DComponent.h"
#include "Render2DComponent.h"

void dae::SpawnFruitCommand::Execute(float)
{
	GameObject* fruit = GetGameObject()->GetScene()->CreateGameObject();
	fruit->SetLocalPosition(GetGameObject()->GetWorldPosition());
	fruit->AddComponent<PickupComponent>(m_Value);
	auto render = fruit->AddComponent<Render2DComponent>();
	render->SetTexture(m_TexturePath);
	auto collider = fruit->AddComponent<Collision2DComponent>(true);
	collider->SetSize(render->GetDimensions());
	collider->EnableDebugDraw();
}
