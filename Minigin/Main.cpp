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
#include "Render2DComponent.h"
#include "FPSComponent.h"
#include "TextComponent.h"
#include "ThrashTheCacheComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "Transform.h"
#include "Orbit.h"
#include "GamepadPlayerController.h"
#include "MovementComponent.h"
#include "KeyboardPlayerController.h"
#include "UIValueTweaker.h"

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

	auto player0 = scene->CreateGameObject();
	player0->SetLocalPosition(glm::vec3{ 150.f, 250.f, .0f });
	player0->AddComponent<Render2DComponent>()->SetTexture("Bubblun.png");
	player0->AddComponent<KeyboardPlayerController>();
	player0->AddComponent<MovementComponent>()->Speed = 50.f;

	valueTweaker->AddPlayer(player0);

	auto player1 = scene->CreateGameObject();
	player1->SetLocalPosition(glm::vec3{ 200.f, 250.f, .0f });
	player1->AddComponent<Render2DComponent>()->SetTexture("Bobblun.png");
	player1->AddComponent<GamepadPlayerController>()->GetGamepad()->SetDeadzone(.7f);
	player1->AddComponent<MovementComponent>()->Speed = 100.f;

	valueTweaker->AddPlayer(player1);
}

int main(int, char*[]) {
	Minigin engine("Data/");
	engine.Run(load);
    return 0;
}