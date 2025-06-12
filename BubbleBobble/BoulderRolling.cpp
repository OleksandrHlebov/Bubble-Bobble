#include "BoulderRolling.h"
#include "GameObject.h"
#include "Scene.h"
#include "Render2DComponent.h"
#include "Collision2DComponent.h"
#include "Animation2DComponent.H"

void dae::BoulderRolling::ExecuteOn(GameObject* gameObject)
{
	GameObject* boulder = gameObject->GetScene()->CreateGameObject();
	auto render = boulder->AddComponent<Render2DComponent>();
	render->SetTexture("Textures/Boulder.png");
	const uint32_t totalFrames{ 6 };
	boulder
		->AddComponent<Collision2DComponent>(true)
		->SetSize(1.f * render->GetDimensions().x / totalFrames, 1.f * render->GetDimensions().y);
	auto otherAnimComp = gameObject->GetComponent<Animation2DComponent>();
	auto anim = boulder->AddComponent<Animation2DComponent>(otherAnimComp->GetFrameTime());
	const uint32_t loops{ 4 };
	anim->PlayCurrent(0, 3, totalFrames, true, loops);
}
