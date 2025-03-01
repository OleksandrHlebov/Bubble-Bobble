#pragma once
#include <SDL_events.h>
#include "Singleton.h"

using namespace dae;

struct SDL_Window;

class ImguiRenderer final : public Singleton<ImguiRenderer>
{
public:
	ImguiRenderer() = default;
	~ImguiRenderer();
	
	ImguiRenderer(const ImguiRenderer&) 				= delete;
	ImguiRenderer(ImguiRenderer&&) noexcept 			= delete;
	ImguiRenderer& operator=(const ImguiRenderer&) 	 	= delete;
	ImguiRenderer& operator=(ImguiRenderer&&) noexcept 	= delete;

	void Init(SDL_Window* window);
	void Render();
	void ProcessEvents(SDL_Event& e);

private:
};