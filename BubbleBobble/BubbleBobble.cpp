#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <iostream>

#pragma region engine
#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "EventDispatcher.h"
#include "GameEvent.h"
#include "Scene.h"
#include "GameObject.h"
#include "AudioLocator.h"
#include "AudioMixer.h"
#pragma endregion engine

#pragma region Components
#include "Render2DComponent.h"
#include "FPSComponent.h"
#include "TextComponent.h"
#include "ThrashTheCacheComponent.h"
#include "Transform.h"
#include "Orbit.h"
#include "GamepadPlayerController.h"
#include "Health.h"
#include "MovementComponent.h"
#include "KeyboardPlayerController.h"
#include "UIValueTweaker.h"
#include "HealthDisplay.h"
#include "Score.h"
#include "AudioHandler.h"
#include "Animation2DComponent.H"
#pragma endregion Components

using namespace dae;

void load()
{
	static AudioMixer audioService{};
	Audio* service{ &audioService };
#ifdef _DEBUG
	static Logger logger{ service };
	service = &logger;
#endif
	AudioLocator::Provide(service);
	AudioLocator::GetService()->SetMasterVolume(.4f);

	auto scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go = scene->CreateGameObject();
	auto font = ResourceManager::GetInstance().LoadFont("arcade-legacy.otf", 16);

	go = scene->CreateGameObject();
	go->AddComponent<Render2DComponent>();
	go->AddComponent<TextComponent>(font);
	go->AddComponent<FPSComponent>();
	go->SetLocalPosition(0, 0);

	font = ResourceManager::GetInstance().LoadFont("arcade-legacy.otf", 8);

	auto manual = scene->CreateGameObject();
	manual->SetLocalPosition(glm::vec3{ 4.f, 68.f, .0f });
	auto player0Controls = scene->CreateGameObject();
	player0Controls->AttachTo(manual);
	player0Controls->AddComponent<Render2DComponent>();
	player0Controls->AddComponent<TextComponent>(font)->SetText("DPad, X burp, A jump, B damage");
	auto player1Controls = scene->CreateGameObject();
	player1Controls->SetLocalPosition(glm::vec3{ .0f, 12.f, .0f });
	player1Controls->AttachTo(manual);
	player1Controls->AddComponent<Render2DComponent>();
	player1Controls->AddComponent<TextComponent>(font)->SetText("AD, Z burp, X jump, C damage");

	auto player0 = scene->CreateGameObject();
	player0->SetLocalPosition(glm::vec3{ 50.f, 160.f, .0f });
	player0->AddComponent<Render2DComponent>()->SetTexture("Textures/Bub_walking.png");
	player0->AddComponent<KeyboardPlayerController>();
	player0->AddComponent<Animation2DComponent>(.08f);
	player0->AddComponent<MovementComponent>()->Speed = 50.f;
	player0->AddComponent<Health>();
	auto player0UI = scene->CreateGameObject();
	player0UI->SetLocalPosition(glm::vec3(4.f, 20.f, .0f));
	auto player0HealthDisplay = scene->CreateGameObject();
	player0HealthDisplay->AttachTo(player0UI);
	player0HealthDisplay->AddComponent<Render2DComponent>();
	player0HealthDisplay->AddComponent<TextComponent>(font);
	player0HealthDisplay->AddComponent<HealthDisplay>()->TrackHealth(player0);
	auto player0Score = scene->CreateGameObject();
	player0Score->AttachTo(player0UI);
	player0Score->SetLocalPosition(glm::vec3(.0f, 12.f, .0f));
	player0Score->AddComponent<Render2DComponent>();
	player0Score->AddComponent<TextComponent>(font);
	player0Score->AddComponent<Score>()->TrackGameObject(player0);

	auto player1 = scene->CreateGameObject();
	player1->SetLocalPosition(glm::vec3{ 50.f, 180.f, .0f });
	player1->AddComponent<Render2DComponent>()->SetTexture("Bobblun.png");
	player1->AddComponent<GamepadPlayerController>()->GetGamepad()->SetDeadzone(.7f);
	player1->AddComponent<Animation2DComponent>(.08f);
	player1->AddComponent<MovementComponent>()->Speed = 100.f;
	player1->AddComponent<Health>();
	auto player1UI = scene->CreateGameObject();
	player1UI->SetLocalPosition(glm::vec3(4.f, 44.f, .0f));
	auto player1HealthDisplay = scene->CreateGameObject();
	player1HealthDisplay->AttachTo(player1UI);
	player1HealthDisplay->AddComponent<Render2DComponent>();
	player1HealthDisplay->AddComponent<TextComponent>(font);
	player1HealthDisplay->AddComponent<HealthDisplay>()->TrackHealth(player1);
	auto player1Score = scene->CreateGameObject();
	player1Score->AttachTo(player1UI);
	player1Score->SetLocalPosition(glm::vec3(.0f, 12.f, .0f));
	player1Score->AddComponent<Render2DComponent>();
	player1Score->AddComponent<TextComponent>(font);
	player1Score->AddComponent<Score>()->TrackGameObject(player1);

	auto audioHandler = scene->CreateGameObject();
	audioHandler->AddComponent<AudioHandler>();

}

int main(int, char* []) {

	Minigin engine("Data/");
	engine.Run(load);

	return 0;
}