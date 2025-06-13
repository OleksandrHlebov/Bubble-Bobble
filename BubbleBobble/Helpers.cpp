#include "Helpers.h"
#include <fstream>
#include <sstream>
#include <cassert>

#include "GameObject.h"
#include "Scene.h"
#include "ResourceManager.h"

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

void dae::CreatePlayer0(Scene* scene, float animationFrameTime)
{
	auto font = ResourceManager::GetInstance().LoadFont("arcade-legacy.otf", 8);
	auto player0 = scene->CreateGameObject();
	player0->SetLocalPosition(glm::vec3{ 30.f, 160.f, .0f });
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
		player0->AddComponent<PlayerController>(std::move(type), false);
	}
	player0->AddComponent<Animation2DComponent>(animationFrameTime);
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

void dae::CreatePlayerAsMaita(Scene* scene, float animationFrameTime)
{
	auto font = ResourceManager::GetInstance().LoadFont("arcade-legacy.otf", 8);

	auto player0 = scene->CreateGameObject();
	player0->SetLocalPosition(glm::vec3{ 30.f, 160.f, .0f });
	auto player0Render = player0->AddComponent<Render2DComponent>();
	player0Render->SetTexture("Textures/Maita_idle.png");
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
		player0->AddComponent<PlayerController>(std::move(type), true);
	}
	player0->AddComponent<Animation2DComponent>(animationFrameTime);
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
