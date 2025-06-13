#include "Helpers.h"
#include <fstream>
#include <sstream>
#include <cassert>

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
#include <array>
#pragma endregion Components

void dae::ReadLevelLayout(const std::string& path, std::vector<bool>& destination)
{
	std::ifstream layoutFile{ path };
	if (!layoutFile.is_open())
	{
		throw std::runtime_error("failed to open layout file");
	}
	std::string line;
	int index{};
	while (std::getline(layoutFile, line))
	{
		std::stringstream sstream{ line };
		while (std::getline(sstream, line, ';'))
		{
			assert(index < std::ssize(destination));
			destination[index++] = std::stoi(line);
		}
	}
}

void dae::CreatePlayer0(Scene* scene, bool usesGamepad)
{
	auto font = ResourceManager::GetInstance().LoadFont("arcade-legacy.otf", 8);
	auto player0 = scene->CreateGameObject();
	player0->SetLocalPosition(glm::vec3{ 30.f, 200.f, .0f });
	auto player0Render = player0->AddComponent<Render2DComponent>();
	player0Render->SetTexture("Textures/Bub_idle.png");
	{
		PlayerType type
		{
			{ "Textures/Bub_idle.png"	, 1 },
			{ "Textures/Bub_walking.png", 4 },
			{ "Textures/Bub_jumping.png", 2 },
			{ "Textures/Bub_falling.png", 2 },
			{ "Textures/Bub_dying.png"	, 6 },
			{ "Textures/Bub_burp.png"	, 1 },
			std::make_unique<BubbleBlowing>()
		};
		player0->AddComponent<PlayerController>(std::move(type), usesGamepad);
	}
	player0->AddComponent<Animation2DComponent>(ANIMATION_FRAMETIME);
	player0->AddComponent<MovementComponent>()->Speed = 50.f;
	const glm::vec2 playerSize{ glm::vec2{ player0Render->GetDimensions() } };
	player0->AddComponent<Collision2DComponent>(true)->SetSize(playerSize);
	player0->AddComponent<Health>();
	auto UI = scene->CreateGameObject();
	UI->SetRenderPriority(RenderPriority::UI);
	UI->SetLocalPosition(glm::vec3(4.f, 20.f, .0f));
	auto healthDisplay = scene->CreateGameObject();
	healthDisplay->AttachTo(UI);
	healthDisplay->AddComponent<Render2DComponent>();
	healthDisplay->AddComponent<TextComponent>(font);
	healthDisplay->AddComponent<HealthDisplay>()->TrackHealth(player0);
	auto score = scene->CreateGameObject();
	score->AttachTo(UI);
	score->SetLocalPosition(glm::vec3(.0f, 12.f, .0f));
	score->AddComponent<Render2DComponent>();
	score->AddComponent<TextComponent>(font);
	score->AddComponent<Score>()->TrackGameObject(player0);
}

void dae::CreatePlayer1(Scene* scene)
{
	auto font = ResourceManager::GetInstance().LoadFont("arcade-legacy.otf", 8);
	auto player0 = scene->CreateGameObject();
	player0->SetLocalPosition(glm::vec3{ 50.f, 200.f, .0f });
	auto player0Render = player0->AddComponent<Render2DComponent>();
	player0Render->SetTexture("Textures/Bub_idle.png");
	{
		PlayerType type
		{
			{ "Textures/Bob_idle.png"	, 1 },
			{ "Textures/Bob_walking.png", 4 },
			{ "Textures/Bob_jumping.png", 2 },
			{ "Textures/Bob_falling.png", 2 },
			{ "Textures/Bob_dying.png"	, 6 },
			{ "Textures/Bob_burp.png"	, 1 },
			std::make_unique<BubbleBlowing>()
		};
		player0->AddComponent<PlayerController>(std::move(type), true);
	}
	player0->AddComponent<Animation2DComponent>(ANIMATION_FRAMETIME);
	player0->AddComponent<MovementComponent>()->Speed = 50.f;
	const glm::vec2 playerSize{ glm::vec2{ player0Render->GetDimensions() } };
	player0->AddComponent<Collision2DComponent>(true)->SetSize(playerSize);
	player0->AddComponent<Health>();
	auto UI = scene->CreateGameObject();
	UI->SetRenderPriority(RenderPriority::UI);
	UI->SetLocalPosition(glm::vec3(4.f, 44.f, .0f));
	auto healthDisplay = scene->CreateGameObject();
	healthDisplay->AttachTo(UI);
	healthDisplay->AddComponent<Render2DComponent>();
	healthDisplay->AddComponent<TextComponent>(font);
	healthDisplay->AddComponent<HealthDisplay>()->TrackHealth(player0);
	auto score = scene->CreateGameObject();
	score->AttachTo(UI);
	score->SetLocalPosition(glm::vec3(.0f, 12.f, .0f));
	score->AddComponent<Render2DComponent>();
	score->AddComponent<TextComponent>(font);
	score->AddComponent<Score>()->TrackGameObject(player0);
}

void dae::CreatePlayerAsMaita(Scene* scene)
{
	auto font = ResourceManager::GetInstance().LoadFont("arcade-legacy.otf", 8);

	auto playableMaita = scene->CreateGameObject();
	playableMaita->SetLocalPosition(glm::vec3{ 200.f, 200.f, .0f });
	auto playableMaitaRender = playableMaita->AddComponent<Render2DComponent>();
	playableMaitaRender->SetTexture("Textures/Maita_idle.png");
	{
		PlayerType type
		{
			{ "Textures/Maita_idle.png"		, 1 },
			{ "Textures/Maita_walking.png"	, 2 },
			{ "Textures/Maita_walking.png"	, 2 },
			{ "Textures/Maita_walking.png"	, 2 },
			{ "Textures/Maita_dead.png"		, 6 },
			{ "Textures/Maita_walking.png"	, 2 },
			std::make_unique<BoulderRolling>()
		};
		playableMaita->AddComponent<PlayerController>(std::move(type), true);
	}
	playableMaita->AddComponent<Animation2DComponent>(ANIMATION_FRAMETIME);
	playableMaita->AddComponent<MovementComponent>()->Speed = 50.f;
	const glm::vec2 playerSize{ glm::vec2{ playableMaitaRender->GetDimensions() } };
	playableMaita->AddComponent<Collision2DComponent>(true)->SetSize(playerSize);
	playableMaita->AddComponent<Health>();
	auto UI = scene->CreateGameObject();
	UI->SetRenderPriority(RenderPriority::UI);
	UI->SetLocalPosition(glm::vec3(4.f, 44.f, .0f));
	auto healthDisplay = scene->CreateGameObject();
	healthDisplay->AttachTo(UI);
	healthDisplay->AddComponent<Render2DComponent>();
	healthDisplay->AddComponent<TextComponent>(font);
	healthDisplay->AddComponent<HealthDisplay>()->TrackHealth(playableMaita);
	auto score = scene->CreateGameObject();
	score->AttachTo(UI);
	score->SetLocalPosition(glm::vec3(.0f, 12.f, .0f));
	score->AddComponent<Render2DComponent>();
	score->AddComponent<TextComponent>(font);
	score->AddComponent<Score>()->TrackGameObject(playableMaita);
}

void dae::CreateScene(const std::string& path, GameMode gameMode)
{
	auto scene = SceneManager::GetInstance().CreateScene("1");

	auto audioHandler = scene->CreateGameObject();
	audioHandler->AddComponent<AudioHandler>();

	std::ifstream levelInfo{ path };
	if (!levelInfo)
	{
		throw std::runtime_error("failed to open level info file " + path);
	}

	std::string tileTexturePath;
	std::string layoutPath;
	std::string element;
	std::getline(levelInfo, element);
	std::stringstream line{ element };
	std::getline(line, tileTexturePath, ';');
	std::getline(line, layoutPath);

	auto levelGrid = scene->CreateGameObject();
	levelGrid->SetRenderPriority(RenderPriority::Background);
	GridComponent* grid = levelGrid->AddComponent<GridComponent>(28, 37, glm::ivec2{ Minigin::GetGameWidth(), Minigin::GetGameHeight() });
	grid->SetTileTexture(ResourceManager::GetInstance().LoadTexture(tileTexturePath));

	grid->LoadLayoutFromFile(layoutPath);
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

	auto font = ResourceManager::GetInstance().LoadFont("arcade-legacy.otf", 8);
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

	switch (gameMode)
	{
	case GameMode::Duo:
		CreatePlayer0(scene, InputManager::GetInstance().GetGamepadCount() > 1);
		CreatePlayer1(scene);
		break;
	case GameMode::Versus:
		CreatePlayer0(scene, InputManager::GetInstance().GetGamepadCount() > 1);
		CreatePlayerAsMaita(scene);
		return;
		break;
	default:
	case GameMode::Solo:
		CreatePlayer0(scene, InputManager::GetInstance().GetGamepadCount() > 0);
		break;
	}

	auto gameInstance = scene->CreateGameObject()->AddComponent<LevelInstance>();

	std::getline(levelInfo, element); // skip description: count, type path
	while (std::getline(levelInfo, element))
	{
		line = std::stringstream{ element };

		std::getline(line, element, ';');
		int enemyCount{ std::stoi(element) };
		std::getline(line, element);
		std::string typePath{ element };
		if (std::ifstream typeInfo{ typePath })
		{
			float speed;
			std::getline(typeInfo, element);
			speed = std::stof(element);
			std::array<std::pair<std::string, int>, 4> props;
			for (auto& prop : props)
			{
				std::getline(typeInfo, element);
				line = std::stringstream{ element };
				std::getline(line, prop.first, ';');
				std::getline(line, element);
				prop.second = std::stoi(element);
			}
			auto [walking, trapped, dead, treat] = std::move(props);
			std::string ability;
			std::getline(typeInfo, ability);

			const AIType& type = gameInstance->AddType(speed, std::move(walking), std::move(trapped), std::move(dead), std::move(treat), ability);

			for (int index{}; index < enemyCount; ++index)
			{
				std::getline(levelInfo, element);
				line = std::stringstream{ element };
				glm::vec2 pos{};
				std::getline(line, element, ';');
				pos.x = std::stof(element);
				std::getline(line, element);
				pos.y = std::stof(element);
				auto enemy = scene->CreateGameObject();
				enemy->SetLocalPosition(glm::vec3{ pos, .0f });
				auto enemyRender = enemy->AddComponent<Render2DComponent>();
				enemyRender->SetTexture(type.WalkingTextureAnim.first);
				enemy->AddComponent<Brain>(type);
				enemy->AddComponent<Animation2DComponent>(ANIMATION_FRAMETIME);
				enemy->AddComponent<MovementComponent>()->Speed = speed;
				const glm::vec2 enemySize{ glm::vec2{ enemyRender->GetDimensions() } *glm::vec2(1.f / type.WalkingTextureAnim.second, 1.f) };
				enemy->AddComponent<Collision2DComponent>(true)->SetSize(enemySize);
			}
		}
		else
			throw std::runtime_error("failed to open " + typePath);
	}
}
