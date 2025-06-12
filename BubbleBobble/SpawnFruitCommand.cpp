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
	fruit->AddComponent<Collision2DComponent>(true);
	fruit->AddComponent<Render2DComponent>()->SetTexture(m_TexturePath);
}
