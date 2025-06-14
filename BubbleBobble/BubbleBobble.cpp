#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <iostream>

#include "BubbleBobble.h"

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
#include "LevelInstanceComponent.h"
#include "PlayerType.h"
#include "Ability.h"
#include "BubbleBlowing.h"
#include "MenuComponent.h"
#pragma endregion Components
#include "Helpers.h"
#include <sstream>

using namespace dae;
using namespace BubbleBobble;

void load()
{
	std::unique_ptr<Audio> service{ std::make_unique<AudioMixer>() };
#ifdef _DEBUG
	service = std::make_unique<Logger>(std::move(service));
#endif
	AudioLocator::Provide(std::move(service));
	AudioLocator::GetService()->SetMasterVolume(.4f);
	static Sound mainTheme{ "Data/SFX/MainTheme.ogg", -1, true };
	AudioLocator::GetService()->Play(&mainTheme);
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
		menu->AddButton("1 player", [&sceneManager](GameObject*,const glm::ivec2& input)
						{
							if (input.y)
							{
								Highscore = 0;
								for (int index{}; index < LEVELS_AVAILABLE; ++index)
									CreateScene("Data/Level/" + std::to_string(index) + "/LevelInfo.csv", std::to_string(index), GameMode::Solo);
								sceneManager.LoadScene("0");
							}
						});
		menu->AddButton("2 player", [&sceneManager](GameObject*, const glm::ivec2& input)
						{
							if (input.y)
							{
								for (int index{}; index < LEVELS_AVAILABLE; ++index)
									CreateScene("Data/Level/" + std::to_string(index) + "/LevelInfo.csv", std::to_string(index), GameMode::Duo);
								sceneManager.LoadScene("0");
							}
						});
		menu->AddButton("Versus", [&sceneManager](GameObject*, const glm::ivec2& input)
						{
							if (input.y)
							{
								int randomLevelIndex{ rand() % LEVELS_AVAILABLE };
								CreateScene("Data/Level/" + std::to_string(randomLevelIndex) + "/LevelInfo.csv", std::to_string(randomLevelIndex), GameMode::Versus);
								sceneManager.LoadScene(std::to_string(randomLevelIndex));
							}
						});
	}

	// endscreen
	{
		auto scene = sceneManager.CreateScene("End");
		{
			GameObject* menuObject = scene->CreateGameObject();
			menuObject->SetLocalPosition(glm::vec3{ 100.f, 60.f, .0f });
			for (int index{}; index < inputManager.GetGamepadCount(); ++index)
				menuObject->AddComponent<PlayerController>(true);
			menuObject->AddComponent<PlayerController>(false);
			auto menu = menuObject->AddComponent<MenuComponent>(font, true);
			for (int index{}; index < 5; ++index)
				menu->AddButton("_", [&sceneManager](GameObject* thisButton, const glm::ivec2& input)
								{
									if (input.x)
									{
										auto textComp = thisButton->GetComponent<TextComponent>();
										char character = textComp->GetText()[0] - static_cast<char>(input.x);
										if (character < 'A')
											character = 'Z';
										if (character > 'Z')
											character = 'A';
										textComp->SetText(std::string(1, character));
									}
									if (input.y)
									{
										// something with leaderboard
										GameObject* menuObject = thisButton->GetParent();
										auto menu = menuObject->GetComponent<MenuComponent>();
										while (!menu)
										{
											menuObject = menuObject->GetParent();
											menu = menuObject->GetComponent<MenuComponent>();
										}
										std::vector<GameObject*> buttons = menu->GetButtons();
										std::string name;
										for (const GameObject* button : buttons)
										{
											auto textComp = button->GetComponent<TextComponent>();
											name += textComp->GetText()[0];
										}
										SaveHighScore(name);
										sceneManager.LoadScene("Leaderboard");
									}
								});
		}
		GameObject* menuObject = scene->CreateGameObject();
		menuObject->SetLocalPosition(glm::vec3{ 100.f, 20.f, .0f });
		for (int index{}; index < inputManager.GetGamepadCount(); ++index)
			menuObject->AddComponent<PlayerController>(true);
		menuObject->AddComponent<PlayerController>(false);
		auto menu = menuObject->AddComponent<MenuComponent>(font, false);
		menu->AddButton("SCORE: ", [](GameObject*, const glm::ivec2&) {}, [](GameObject* gameObject)
						{
							auto textComp = gameObject->GetComponent<TextComponent>();
							textComp->SetText("SCORE: " + std::to_string(BubbleBobble::Highscore));
						});
		
	}

	// leaderboard
	{

		auto scene = sceneManager.CreateScene("Leaderboard");

		{
			GameObject* menuObject = scene->CreateGameObject();
			menuObject->SetLocalPosition(glm::vec3{ 100.f, 30.f, .0f });
			auto menu = menuObject->AddComponent<MenuComponent>(font, false);
			for (int index{}; index < 5; ++index)
				menu->AddButton("name: score", [](GameObject*, const glm::ivec2&) {});
			menu->AddButton(" ", [](GameObject*, const glm::ivec2&) {}, [](GameObject* thisButton)
							{
								GameObject* menuObject = thisButton->GetParent();
								auto menu = menuObject->GetComponent<MenuComponent>();
								while (!menu)
								{
									menuObject = menuObject->GetParent();
									menu = menuObject->GetComponent<MenuComponent>();
								}
								auto& buttons = menu->GetButtons();
								auto highscores = LoadHighestScores();
								for (int index{}; index < highscores.size(); ++index)
								{
									std::stringstream ss; 
									ss << highscores[index].first << ": " << std::to_string(highscores[index].second);
									buttons[index]->GetComponent<TextComponent>()->SetText(ss.str());
								}
							});
		}
		{
			GameObject* menuObject = scene->CreateGameObject();
			menuObject->SetLocalPosition(glm::vec3{ 70.f, 200.f, .0f });
			for (int index{}; index < inputManager.GetGamepadCount(); ++index)
				menuObject->AddComponent<PlayerController>(true);
			menuObject->AddComponent<PlayerController>(false);
			auto menu = menuObject->AddComponent<MenuComponent>(font, true);
			menu->AddButton("Back to menu", [&sceneManager](GameObject*, const glm::ivec2& input)
							{
								if (input.y)
								{
									sceneManager.LoadScene("Menu");
								}
							});
		}
	}
}

int main(int, char* []) {

	Minigin engine("Data/");
	engine.Run(load);

	return 0;
}