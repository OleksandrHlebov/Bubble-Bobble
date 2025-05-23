#include "ImguiRenderer.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "imgui.h"
#include "imgui_plot.h"
#include "backends\imgui_impl_sdl2.h"
#include "backends\imgui_impl_opengl3.h"

dae::ImguiRenderer::~ImguiRenderer()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

void dae::ImguiRenderer::Init(SDL_Window* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL3_Init();
}

void dae::ImguiRenderer::Render()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void dae::ImguiRenderer::NewFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
}

void dae::ImguiRenderer::ProcessEvents(SDL_Event& e)
{
	ImGui_ImplSDL2_ProcessEvent(&e);
}
