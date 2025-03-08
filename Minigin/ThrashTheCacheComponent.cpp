#include "ThrashTheCacheComponent.h"
#include "TrashTheCache.h"
#include "imgui.h"
#include "imgui_plot.h"

void dae::ThrashTheCacheComponent::RenderUI()
{
	RenderExercise1();
	RenderExercise2();
}

void dae::ThrashTheCacheComponent::RenderExercise1()
{
	ImGui::SetNextWindowSize(ImVec2{ 300., 300. }, ImGuiCond_Once);
	ImGui::SetNextWindowPos(ImVec2{ .0f, .0f }, ImGuiCond_Once);
	ImGui::Begin("Exercise 1");
	ImGui::InputInt("Samples##IINT01", &m_Ex1Samples, 1, 100);
	if (m_Ex1Samples < 1) m_Ex1Samples = 1;
	if (ImGui::Button("Trash the cache##BUT01"))
	{
		ttc::TestInts(m_Ex1Samples, m_Ex1Results);
	}
	if (!m_Ex1Results.empty())
	{
		ImGui::PlotConfig config{};
		config.tooltip.show = true;
		config.scale.min = 0;
		config.scale.max = *std::max_element(m_Ex1Results.begin(), m_Ex1Results.end());
		config.values.ys = m_Ex1Results.data();
		config.values.count = (int)m_Ex1Results.size();
		config.frame_size = ImVec2(200.f, 100.f);
		ImGui::Plot("##PLOT01", config);
	}
	ImGui::End();
}

void dae::ThrashTheCacheComponent::RenderExercise2()
{
	ImGui::SetNextWindowSize(ImVec2{ 300., 300. }, ImGuiCond_Once);
	ImGui::SetNextWindowPos(ImVec2{ 325., .0f }, ImGuiCond_Once);
	ImGui::Begin("Exercise 2");
	ImGui::InputInt("Samples##IINT02", &m_Ex2Samples, 1, 100);
	if (m_Ex2Samples < 1) m_Ex2Samples = 1;
	if (ImGui::Button("Trash the cache with GameObject##BUT02"))
	{
		ttc::TestObjects(m_Ex2Samples, m_Ex2Results);
	}
	if (!m_Ex2Results.empty())
	{
		ImGui::PlotConfig config{};
		config.tooltip.show = true;
		config.scale.min = 0;
		config.scale.max = *std::max_element(m_Ex2Results.begin(), m_Ex2Results.end());
		config.values.ys = m_Ex2Results.data();
		config.values.count = (int)m_Ex2Results.size();
		config.frame_size = ImVec2(200.f, 100.f);
		ImGui::Plot("##PLOT02", config);
	}
	if (ImGui::Button("Trash the cache wih GameObjectAlt##BUT03"))
	{
		ttc::TestObjectsAlt(m_Ex2Samples, m_Ex2ResultsAlt);
	}
	if (!m_Ex2ResultsAlt.empty())
	{
		ImGui::PlotConfig config{};
		config.tooltip.show = true;
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
		config.tooltip.show = true;
		config.scale.min = 0;
		config.scale.max = std::max(*std::max_element(m_Ex2ResultsAlt.begin(), m_Ex2ResultsAlt.end()),
			*std::max_element(m_Ex2Results.begin(), m_Ex2Results.end()));
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
