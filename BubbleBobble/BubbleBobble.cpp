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
#include "Brain.h"
#include "Render2DComponent.h"
#include "FPSComponent.h"
#include "TextComponent.h"
#include "Transform.h"
#include "PlayerController.h"
#include "Health.h"
#include "MovementComponent.h"
#include "HealthDisplay.h"
#include "Score.h"
#include "AudioHandler.h"
#include "Animation2DComponent.H"
#include "GridComponent.h"
#include "Collision2DComponent.h"
#include "RenderPriorities.h"
#include "GameInstanceComponent.h"
#pragma endregion Components

using namespace dae;

void load()
{
	std::unique_ptr<Audio> service{ std::make_unique<AudioMixer>() };
#ifdef _DEBUG
	service = std::make_unique<Logger>(std::move(service));
#endif
	AudioLocator::Provide(std::move(service));
	AudioLocator::GetService()->SetMasterVolume(.4f);

	auto scene = SceneManager::GetInstance().CreateScene("Demo");

	auto gameInstance = scene->CreateGameObject()->AddComponent<GameInstance>();

	auto levelGrid = scene->CreateGameObject();
	levelGrid->SetRenderPriority(static_cast<int>(RenderPriority::Background));
	GridComponent* grid = levelGrid->AddComponent<GridComponent>(28, 37, glm::ivec2{ Minigin::GetGameWidth(), Minigin::GetGameHeight() });

	grid->EnableColumn(0);
	grid->EnableColumn(1);
	grid->EnableColumn(36);
	grid->EnableColumn(35);

	grid->DisableRow(0);
	grid->DisableRow(1);
	grid->DisableRow(2);

	grid->EnableRow(12);
	grid->EnableRow(17);
	grid->EnableRow(22);

	grid->DisableColumn(6);
	grid->DisableColumn(7);
	grid->DisableColumn(8);

	grid->DisableColumn(30);
	grid->DisableColumn(29);
	grid->DisableColumn(28);

	grid->EnableRow(3);
	grid->DisableTile(17 + 37 * 3);
	grid->DisableTile(18 + 37 * 3);
	grid->DisableTile(19 + 37 * 3);
	grid->EnableRow(27);

	auto go = scene->CreateGameObject();
	auto font = ResourceManager::GetInstance().LoadFont("arcade-legacy.otf", 16);

	go = scene->CreateGameObject();
	go->SetRenderPriority(static_cast<int>(RenderPriority::UI));
	go->AddComponent<Render2DComponent>();
	go->AddComponent<TextComponent>(font);
	go->AddComponent<FPSComponent>();
	go->SetLocalPosition(0, 0);

	font = ResourceManager::GetInstance().LoadFont("arcade-legacy.otf", 8);

	auto manual = scene->CreateGameObject();
	manual->SetRenderPriority(static_cast<int>(RenderPriority::UI));
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
	player0->SetLocalPosition(glm::vec3{ 30.f, 160.f, .0f });
	auto player0Render = player0->AddComponent<Render2DComponent>();
	player0Render->SetTexture("Textures/Bub_walking.png");
	player0->AddComponent<PlayerController>(false);
	player0->AddComponent<Animation2DComponent>(.08f);
	player0->AddComponent<MovementComponent>()->Speed = 50.f;
	{
		const int framesInTexture{ 4 };
		const glm::vec2 playerSize{ glm::vec2{ player0Render->GetDimensions() } *glm::vec2(1.f / framesInTexture, 1.f) };
		player0->AddComponent<Collision2DComponent>(true)->SetSize(playerSize);
	}
	player0->AddComponent<Health>();
	auto player0UI = scene->CreateGameObject();
	player0UI->SetRenderPriority(static_cast<int>(RenderPriority::UI));
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
	player1->AddComponent<PlayerController>()->GetGamepad()->SetDeadzone(.7f);
	player1->AddComponent<Animation2DComponent>(.08f);
	player1->AddComponent<MovementComponent>()->Speed = 100.f;
	{
		const int framesInTexture{ 4 };
		const glm::vec2 playerSize{ glm::vec2{ player0Render->GetDimensions() } *glm::vec2(1.f / framesInTexture, 1.f) };
		player1->AddComponent<Collision2DComponent>(true)->SetSize(playerSize);
	}
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

	auto zen = scene->CreateGameObject();
	zen->SetLocalPosition(glm::vec3{ 50.f, 20.f, .0f });
	auto zenRender = zen->AddComponent<Render2DComponent>();
	zenRender->SetTexture("Textures/Zen_walking.png");
	zen->AddComponent<Brain>(gameInstance->GetZenType());
	zen->AddComponent<Animation2DComponent>(.08f);
	zen->AddComponent<MovementComponent>()->Speed = 100.f;
	{
		const int framesInTexture{ 2 };
		const glm::vec2 zenSize{ glm::vec2{ zenRender->GetDimensions() } *glm::vec2(1.f / framesInTexture, 1.f) };
		zen->AddComponent<Collision2DComponent>(true)->SetSize(zenSize);
	}

	auto audioHandler = scene->CreateGameObject();
	audioHandler->AddComponent<AudioHandler>();

}

int main(int, char* []) {

	Minigin engine("Data/");
	engine.Run(load);

	return 0;
}