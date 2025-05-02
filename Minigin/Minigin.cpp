#pragma region sdl
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#pragma endregion sdl
#pragma region stl
#include <stdexcept>
#include <cmath>
#include <thread>
#include <cinttypes>
#include <iostream>
#include <cfloat>
#pragma endregion stl
#pragma region engine
#include "Minigin.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "EventDispatcher.h"
#include "AudioLocator.h"
#include "AudioMixer.h"
#pragma endregion engine

SDL_Window* g_window{};

void PrintSDLVersion()
{
	SDL_version version{};
	SDL_VERSION(&version);
	printf("We compiled against SDL version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	SDL_GetVersion(&version);
	printf("We are linking against SDL version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_IMAGE_VERSION(&version);
	printf("We compiled against SDL_image version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *IMG_Linked_Version();
	printf("We are linking against SDL_image version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_TTF_VERSION(&version)
	printf("We compiled against SDL_ttf version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *TTF_Linked_Version();
	printf("We are linking against SDL_ttf version %u.%u.%u.\n",
		version.major, version.minor, version.patch);
}

dae::Minigin::Minigin(const std::string &dataPath)
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(g_window);

	SDL_RenderSetLogicalSize(Renderer::GetInstance().GetSDLRenderer(), LOGICAL_WINDOW_WIDTH, LOGICAL_WINDOW_HEIGHT);

	ResourceManager::GetInstance().Init(dataPath);

	if (SDL_RenderSetVSync(SDL_GetRenderer(g_window), VSYNC_ON))
		std::cout << "vsync failed";
}

dae::Minigin::~Minigin()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run(const std::function<void()>& load)
{
	load();

	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();
	auto& resourceManager = ResourceManager::GetInstance();
	auto& eventDispatcher = EventDispatcher::GetInstance();

	input.Init();
	sceneManager.Start();

	bool doContinue = true;
	auto lastTime = std::chrono::steady_clock::now();
	float lag{};
	float unloadResorcesTimer{};
	while (doContinue)
	{
		const auto currentTime = std::chrono::steady_clock::now();
		const float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();

		lastTime = currentTime;
		lag += deltaTime;
		unloadResorcesTimer += deltaTime;

		doContinue = input.ProcessInput(deltaTime);
		sceneManager.Update(deltaTime);
		while (lag >= FIXED_UPDATE_TIME)
		{
			sceneManager.FixedUpdate(FIXED_UPDATE_TIME);
			lag -= FIXED_UPDATE_TIME;
		}
		eventDispatcher.HandleDispatchedEvents();
		renderer.Render();

		if (unloadResorcesTimer >= RESOURCES_UNLOAD_TIME)
		{
			resourceManager.UnloadUnusedResources();
			unloadResorcesTimer = 0.f;
		}

		std::chrono::nanoseconds newDeltaTime{ currentTime - std::chrono::steady_clock::now() };

		std::this_thread::sleep_for(newDeltaTime + std::chrono::milliseconds(MS_PER_FRAME));
	}
}
