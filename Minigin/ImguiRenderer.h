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
		void ProcessEvents(SDL_Event& e);

	private:
		void InternalRender();
		void DrawExercise1();
		void DrawExercise2();

		std::vector<float> m_Ex1Results;
		std::vector<float> m_Ex2Results;
		std::vector<float> m_Ex2ResultsAlt;

		int m_Ex1Samples{ 10 };
		int m_Ex2Samples{ 10 };
	};
}