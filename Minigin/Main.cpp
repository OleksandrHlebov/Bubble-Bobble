#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <iostream>

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "EventDispatcher.h"
#include "Render2DComponent.h"
#include "FPSComponent.h"
#include "TextComponent.h"
#include "ThrashTheCacheComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "Transform.h"
#include "Orbit.h"
#include "GameEvent.h"
#include "GamepadPlayerController.h"
#include "Health.h"
#include "MovementComponent.h"
#include "KeyboardPlayerController.h"
#include "UIValueTweaker.h"
#include "HealthDisplay.h"
#include "Score.h"
#include "PickUpComponent.h"

using namespace dae;

void load()
{
	auto scene = SceneManager::GetInstance().CreateScene("Demo");

	auto UI = scene->CreateGameObject();
	auto valueTweaker = UI->AddComponent<UIValueTweaker>();

	auto background = scene->CreateGameObject();
	auto goRenderComponent = background->AddComponent<Render2DComponent>();
	goRenderComponent->SetTexture("background.tga");

	auto logo = scene->CreateGameObject();
	goRenderComponent = logo->AddComponent<Render2DComponent>();
	goRenderComponent->SetTexture("logo.tga");
	logo->SetLocalPosition(216, 180);

	auto go = scene->CreateGameObject();
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto textComponent = go->AddComponent<TextComponent>(font);
	textComponent->SetText("Programming 4 Assignment");
	go->SetLocalPosition(80, 16);

	go = scene->CreateGameObject();
	go->AddComponent<TextComponent>(font);
	go->AddComponent<FPSComponent>();
	go->SetLocalPosition(0, 64);

	auto bubblun = scene->CreateGameObject();
	auto bubblunRender = bubblun->AddComponent<Render2DComponent>();
	bubblunRender->SetTexture("Bubblun.png");
	auto orbit = bubblun->AddComponent<Orbit>();
	orbit->SetPosition({ 300.f, 300.f, .0f });

	auto bobblun = scene->CreateGameObject();
	auto bobblunRender = bobblun->AddComponent<Render2DComponent>();
	bobblunRender->SetTexture("Bobblun.png");
	bobblun->AttachTo(bubblun, false);
	orbit = bobblun->AddComponent<Orbit>();
	orbit->SetSpeed(12);
	auto thrashTheCache = scene->CreateGameObject();
	thrashTheCache->AddComponent<ThrashTheCacheComponent>();

	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 14);

	auto player0 = scene->CreateGameObject();
	player0->SetLocalPosition(glm::vec3{ 150.f, 250.f, .0f });
	player0->AddComponent<Render2DComponent>()->SetTexture("Bubblun.png");
	player0->AddComponent<KeyboardPlayerController>();
	player0->AddComponent<MovementComponent>()->Speed = 50.f;
	player0->AddComponent<Health>();
	player0->AddComponent<PickUpComponent>(15.f);
	auto player0UI = scene->CreateGameObject();
	player0UI->SetLocalPosition(glm::vec3(20.f, 200.f, .0f));
	auto player0HealthDisplay = scene->CreateGameObject();
	player0HealthDisplay->AttachTo(player0UI);
	player0HealthDisplay->AddComponent<TextComponent>(font);
	player0HealthDisplay->AddComponent<HealthDisplay>()->TrackHealth(player0);
	auto player0Score = scene->CreateGameObject();
	player0Score->AttachTo(player0UI);
	player0Score->SetLocalPosition(glm::vec3(.0f, 15.f, .0f));
	player0Score->AddComponent<TextComponent>(font);
	player0Score->AddComponent<Score>()->TrackGameObject(player0);

	valueTweaker->AddPlayer(player0);

	auto player1 = scene->CreateGameObject();
	player1->SetLocalPosition(glm::vec3{ 200.f, 250.f, .0f });
	player1->AddComponent<Render2DComponent>()->SetTexture("Bobblun.png");
	player1->AddComponent<GamepadPlayerController>()->GetGamepad()->SetDeadzone(.7f);
	player1->AddComponent<MovementComponent>()->Speed = 100.f;
	player1->AddComponent<Health>();
	player1->AddComponent<PickUpComponent>(15.f);
	auto player1UI = scene->CreateGameObject();
	player1UI->SetLocalPosition(glm::vec3(20.f, 230.f, .0f));
	auto player1HealthDisplay = scene->CreateGameObject();
	player1HealthDisplay->AttachTo(player1UI);
	player1HealthDisplay->AddComponent<TextComponent>(font);
	player1HealthDisplay->AddComponent<HealthDisplay>()->TrackHealth(player1);
	auto player1Score = scene->CreateGameObject();
	player1Score->AttachTo(player1UI);
	player1Score->SetLocalPosition(glm::vec3(.0f, 15.f, .0f));
	player1Score->AddComponent<TextComponent>(font);
	player1Score->AddComponent<Score>()->TrackGameObject(player1);

	valueTweaker->AddPlayer(player1);

}

int main(int, char*[]) {
	Minigin engine("Data/");
	engine.Run(load);
    return 0;
}