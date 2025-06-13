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
#include "PlayerType.h"
#include "Ability.h"
#include "BubbleBlowing.h"
#pragma endregion Components
#include "Helpers.h"

using namespace dae;

void load()
{
	const float animationFrameTime{ .16f };
	
	std::unique_ptr<Audio> service{ std::make_unique<AudioMixer>() };
#ifdef _DEBUG
	service = std::make_unique<Logger>(std::move(service));
#endif
	AudioLocator::Provide(std::move(service));
	AudioLocator::GetService()->SetMasterVolume(.4f);
	SceneManager& sceneManager = SceneManager::GetInstance();
	auto font = ResourceManager::GetInstance().LoadFont("arcade-legacy.otf", 16);

	// menu
	{
		//auto scene = sceneManager.CreateScene("Menu");
		//scene;
	}

	// level 1
	{
		auto scene = sceneManager.CreateScene("1");

		auto gameInstance = scene->CreateGameObject()->AddComponent<GameInstance>();

		auto audioHandler = scene->CreateGameObject();
		audioHandler->AddComponent<AudioHandler>();

		auto levelGrid = scene->CreateGameObject();
		levelGrid->SetRenderPriority(RenderPriority::Background);
		GridComponent* grid = levelGrid->AddComponent<GridComponent>(28, 37, glm::ivec2{ Minigin::GetGameWidth(), Minigin::GetGameHeight() });

		grid->LoadLayoutFromFile("Data/Level/1/Layout.csv");
		//grid->EnableColumn(0);
		//grid->EnableColumn(1);
		//grid->EnableColumn(36);
		//grid->EnableColumn(35);

		//grid->DisableRow(0);
		//grid->DisableRow(1);
		//grid->DisableRow(2);

		//grid->EnableRow(12);
		//grid->EnableRow(17);
		//grid->EnableRow(22);

		//grid->DisableColumn(6);
		//grid->DisableColumn(7);
		//grid->DisableColumn(8);

		//grid->DisableColumn(30);
		//grid->DisableColumn(29);
		//grid->DisableColumn(28);

		//grid->EnableRow(3);
		//grid->DisableTile(17 + 37 * 3);
		//grid->DisableTile(18 + 37 * 3);
		//grid->DisableTile(19 + 37 * 3);
		//grid->EnableRow(27);

		//auto go = scene->CreateGameObject();

		font = ResourceManager::GetInstance().LoadFont("arcade-legacy.otf", 8);
		auto manual = scene->CreateGameObject();
		manual->SetRenderPriority(RenderPriority::UI);
		manual->SetLocalPosition(glm::vec3{ 4.f, 68.f, .0f });
		auto controls = scene->CreateGameObject();
		controls->AttachTo(manual);
		controls->AddComponent<Render2DComponent>();
		controls->AddComponent<TextComponent>(font)->SetText("DPad, X burp, A jump, B damage");
		auto player1Controls = scene->CreateGameObject();
		player1Controls->SetLocalPosition(glm::vec3{ .0f, 12.f, .0f });
		player1Controls->AttachTo(manual);
		player1Controls->AddComponent<Render2DComponent>();
		player1Controls->AddComponent<TextComponent>(font)->SetText("AD, Z burp, X jump, C damage");


		dae::CreatePlayer0(scene, animationFrameTime);

		//dae::CreatePlayerAsMaita(scene, animationFrameTime);

		auto zen = scene->CreateGameObject();
		zen->SetLocalPosition(glm::vec3{ 50.f, 20.f, .0f });
		auto zenRender = zen->AddComponent<Render2DComponent>();
		zenRender->SetTexture("Textures/Zen_walking.png");
		zen->AddComponent<Brain>(gameInstance->GetZenType());
		zen->AddComponent<Animation2DComponent>(animationFrameTime);
		zen->AddComponent<MovementComponent>()->Speed = 75.f;
		{
			const int framesInTexture{ 2 };
			const glm::vec2 zenSize{ glm::vec2{ zenRender->GetDimensions() } *glm::vec2(1.f / framesInTexture, 1.f) };
			zen->AddComponent<Collision2DComponent>(true)->SetSize(zenSize);
		}

		auto maita = scene->CreateGameObject();
		maita->SetLocalPosition(glm::vec3{ 150.f, 20.f, .0f });
		auto maitaRender = maita->AddComponent<Render2DComponent>();
		maitaRender->SetTexture("Textures/Maita_walking.png");
		maita->AddComponent<Brain>(gameInstance->GetMaitaType());
		maita->AddComponent<Animation2DComponent>(animationFrameTime);
		maita->AddComponent<MovementComponent>()->Speed = 50.f;
		{
			const int framesInTexture{ 2 };
			const glm::vec2 maitaSize{ glm::vec2{ maitaRender->GetDimensions() } *glm::vec2(1.f / framesInTexture, 1.f) };
			maita->AddComponent<Collision2DComponent>(true)->SetSize(maitaSize);
		}
	}
}

int main(int, char* []) {

	Minigin engine("Data/");
	engine.Run(load);

	return 0;
}