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
#include "MenuComponent.h"
#pragma endregion Components
#include "Helpers.h"

using namespace dae;

void load()
{
	std::unique_ptr<Audio> service{ std::make_unique<AudioMixer>() };
#ifdef _DEBUG
	service = std::make_unique<Logger>(std::move(service));
#endif
	AudioLocator::Provide(std::move(service));
	AudioLocator::GetService()->SetMasterVolume(.4f);
	SceneManager& sceneManager = SceneManager::GetInstance();
	auto font = ResourceManager::GetInstance().LoadFont("arcade-legacy.otf", 8);
	InputManager& inputManager = InputManager::GetInstance();

	// menu
	{
		auto scene = sceneManager.CreateScene("Menu");
		
		GameObject* menuObject = scene->CreateGameObject();
		menuObject->SetLocalPosition(glm::vec3{ 100.f, 60.f, .0f });
		for (int index{}; index < inputManager.GetGamepadCount(); ++index)
			menuObject->AddComponent<PlayerController>(true);
		menuObject->AddComponent<PlayerController>(false);
		auto menu = menuObject->AddComponent<MenuComponent>(font);
		menu->AddButton("1 player", [&sceneManager](const glm::ivec2& input)
						{
							if (input.y)
							{
								CreateScene("Data/Level/1/Layout.csv", GameMode::Solo);
								sceneManager.LoadScene("1");
							}
						});
		menu->AddButton("2 player", [&sceneManager](const glm::ivec2& input)
						{
							if (input.y)
							{
								CreateScene("Data/Level/1/Layout.csv", GameMode::Duo);
								sceneManager.LoadScene("1");
							}
						});
		menu->AddButton("Versus", [&sceneManager](const glm::ivec2& input)
						{
							if (input.y)
							{
								CreateScene("Data/Level/1/Layout.csv", GameMode::Versus);
								sceneManager.LoadScene("1");
							}
						});
	}
}

int main(int, char* []) {

	Minigin engine("Data/");
	engine.Run(load);

	return 0;
}