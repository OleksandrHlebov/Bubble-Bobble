#include "ImguiRenderer.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "imgui.h"
#include "imgui_plot.h"
#include "backends\imgui_impl_sdl2.h"
#include "backends\imgui_impl_opengl3.h"
#include "TrashTheCache.h"
ImguiRenderer::~ImguiRenderer()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

void ImguiRenderer::Init(SDL_Window* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL3_Init();
}

void ImguiRenderer::Render()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
	InternalRender();
	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImguiRenderer::ProcessEvents(SDL_Event& e)
{
	ImGui_ImplSDL2_ProcessEvent(&e);
}

void ImguiRenderer::InternalRender()
{
	DrawExercise1();

	DrawExercise2();
}

void ImguiRenderer::DrawExercise1()
{
	ImGui::SetNextWindowSize(ImVec2{ 300., 300. }, ImGuiCond_Once);
	ImGui::SetNextWindowPos(ImVec2{ .0f, .0f }, ImGuiCond_Once);
	ImGui::Begin("Exercise 1");
	ImGui::InputInt("Samples##IINT01", &m_Ex1Samples, 1, 100);
	if (ImGui::Button("Trash the cache##BUT01"))
	{
		ttc::TestInts(m_Ex1Samples, m_Ex1Results);
	}
	if (!m_Ex1Results.empty())
	{
		ImGui::PlotConfig config{};
		config.scale.min	= 0;
		config.scale.max	= *std::max_element(m_Ex1Results.begin(), m_Ex1Results.end());
		config.values.ys	= m_Ex1Results.data();
		config.values.count = (int) m_Ex1Results.size();
		config.frame_size	= ImVec2(200.f, 100.f);
		ImGui::Plot("##PLOT01", config);
	}
	ImGui::End();
}

void ImguiRenderer::DrawExercise2()
{
	ImGui::SetNextWindowSize(ImVec2{ 300., 300. }, ImGuiCond_Once);
	ImGui::SetNextWindowPos(ImVec2{ 325., .0f }, ImGuiCond_Once);
	ImGui::Begin("Exercise 2");
	ImGui::InputInt("Samples##IINT02", &m_Ex2Samples, 1, 100);
	if (ImGui::Button("Trash the cache with GameObject##BUT02"))
	{
		ttc::TestObjects(m_Ex2Samples, m_Ex2Results);
	}
	if (!m_Ex2Results.empty())
	{
		ImGui::PlotConfig config{};
		config.scale.min	= 0;
		config.scale.max	= *std::max_element(m_Ex2Results.begin(), m_Ex2Results.end());
		config.values.ys	= m_Ex2Results.data();
		config.values.count = (int)m_Ex2Results.size();
		config.frame_size	= ImVec2(200.f, 100.f);
		ImGui::Plot("##PLOT02", config);
	}
	if (ImGui::Button("Trash the cache wih GameObjectAlt##BUT03"))
	{
		ttc::TestObjectsAlt(m_Ex2Samples, m_Ex2ResultsAlt);
	}
	if (!m_Ex2ResultsAlt.empty())
	{
		ImGui::PlotConfig config{};
		config.scale.min = 0;
		config.scale.max = *std::max_element(m_Ex2ResultsAlt.begin(), m_Ex2ResultsAlt.end());
		config.values.ys = m_Ex2ResultsAlt.data();
		config.values.count = (int)m_Ex2ResultsAlt.size();
		config.frame_size = ImVec2(200.f, 100.f);
		ImGui::Plot("##PLOT03", config);
	}
	if (!m_Ex2Results.empty() && !m_Ex2ResultsAlt.empty())
	{
		ImGui::PlotConfig config{};
		config.scale.min = 0;
		config.scale.max = std::max(*std::max_element(m_Ex2ResultsAlt.begin(), m_Ex2ResultsAlt.end()),
									*std::max_element(m_Ex2Results.begin()	 , m_Ex2Results.end()));
		const float* list[2]{ m_Ex2Results.data(), m_Ex2ResultsAlt.data() };
		config.values.ys_count = 2;
		config.values.ys_list = list;
		config.values.count = (int)m_Ex2ResultsAlt.size();
		config.frame_size = ImVec2(200.f, 100.f);
		ImGui::Text("Combined graph");
		ImGui::Plot("Combined graph##PLOT04", config);
	}
	ImGui::End();
}
