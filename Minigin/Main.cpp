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
#include "GameObject.h"
#include "Scene.h"
#include "Transform.h"
#include "Orbit.h"

using namespace dae;

void load()
{
	auto scene = SceneManager::GetInstance().CreateScene("Demo");

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
	bobblun->SetParent(bubblun, true);
	orbit = bobblun->AddComponent<Orbit>();
	orbit->SetSpeed(12);
}

int main(int, char*[]) {
	Minigin engine("Data/");
	engine.Run(load);
    return 0;
}