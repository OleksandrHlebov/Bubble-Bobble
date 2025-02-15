#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Render2DComponent.h"
#include "FPSComponent.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "Transform.h"

using namespace dae;

void load()
{
	auto scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go = scene->CreateGameObject();
	auto goRenderComponent = go->AddComponent<Render2DComponent>();
	goRenderComponent->SetTexture("background.tga");

	go = scene->CreateGameObject();
	goRenderComponent = go->AddComponent<Render2DComponent>();
	goRenderComponent->SetTexture("logo.tga");
	go->SetPosition(216, 180);

	go = scene->CreateGameObject();
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto textComponent = go->AddComponent<TextComponent>(font);
	textComponent->SetText("Programming 4 Assignment");
	go->SetPosition(80, 16);

	go = scene->CreateGameObject();
	go->AddComponent<FPSComponent>(font);
	go->SetPosition(0, 64);
}

int main(int, char*[]) {
	Minigin engine("Data/");
	engine.Run(load);
    return 0;
}