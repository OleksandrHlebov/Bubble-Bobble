#pragma once
#include <SDL_events.h>
#include <vector>
#include "Singleton.h"

struct SDL_Window;

namespace dae
{
	class ImguiRenderer final : public Singleton<ImguiRenderer>
	{
	public:
		ImguiRenderer() = default;
		~ImguiRenderer();

		ImguiRenderer(const ImguiRenderer&) = delete;
		ImguiRenderer(ImguiRenderer&&) noexcept = delete;
		ImguiRenderer& operator=(const ImguiRenderer&) = delete;
		ImguiRenderer& operator=(ImguiRenderer&&) noexcept = delete;

		void Init(SDL_Window* window);
		void Render();
		void NewFrame();
		void ProcessEvents(SDL_Event& e);

	private:

	};
}