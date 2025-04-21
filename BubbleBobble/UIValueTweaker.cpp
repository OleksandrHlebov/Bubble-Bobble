#include "UIValueTweaker.h"
#include "imgui.h"
#include <iostream>
#include <sstream>
#include "GameObject.h"
#include "MovementComponent.h"
#include "GamepadPlayerController.h"
#include "AudioLocator.h"

void dae::UIValueTweaker::AddPlayer(GameObject* player)
{
	if (std::find(m_Players.begin(), m_Players.end(), player) != m_Players.end())
	{
		std::cout << "[ValueTweaker] Attempting to add player already in container\n";
		return;
	}
	MovementComponent* movement = player->GetComponent<MovementComponent>();
	if (!movement)
	{
		std::cout << "[ValueTweaker] Object invalid. Missing movement component\n";
		return;
	}

	m_Players.emplace_back(player);
}

void dae::UIValueTweaker::RenderUI()
{
	ImGui::SetNextWindowPos(ImVec2{ 375.f, 20.f }, ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2{ 250.f, 250.f }, ImGuiCond_Once);
	ImGui::Begin("Value tweaker", NULL, ImGuiWindowFlags_NoResize);

	if (ImGui::CollapsingHeader("Settings", NULL, ImGuiTreeNodeFlags_Framed))
	{
		ImGui::PushID("VLM");
		float volume{ AudioLocator::GetService()->GetMasterVolume() };
		ImGui::SliderFloat("Volume", &volume, .0f, 1.f, "%.2f");
		AudioLocator::GetService()->SetMasterVolume(volume);
		ImGui::PopID();
	}

	for (int index{}; index < m_Players.size(); ++index)
	{
		GameObject* player = m_Players[index];
		MovementComponent* movement = player->GetComponent<MovementComponent>();

		ImGui::SetNextItemWidth(200.f);
		ImGui::Spacing();
		if (ImGui::CollapsingHeader(("player" + std::to_string(index)).c_str(), NULL, ImGuiTreeNodeFlags_Framed))
		{
			ImGui::PushID("SPD" + index);
			ImGui::SliderFloat("Speed", &movement->Speed, 1.f, 200.f, "%.1f");
			ImGui::PopID();
			GamepadPlayerController* playerController = player->GetComponent<GamepadPlayerController>();
			if (playerController)
			{
				Gamepad* gamepad = playerController->GetGamepad();
				if (gamepad->IsConnected())
				{
#ifdef _DEBUG
					ImGui::PushID("INP" + index);
					std::stringstream ss;
					ss << "Thumbstick input: " << gamepad->DEBUG_GetLeftThumbInput().x << ' ' << gamepad->DEBUG_GetLeftThumbInput().y;
					ImGui::Text(ss.str().c_str());
					ImGui::PopID();
#endif
					float deadzone = gamepad->GetDeadzone();
					ImGui::PushID("DDZ" + index);
					ImGui::SliderFloat("Deadzone", &deadzone, .0f, 1.f, "%.2f");
					ImGui::PopID();
					gamepad->SetDeadzone(deadzone);
				}
				else
				{
					ImGui::PushID("TXT" + index);
					ImGui::Text("Gamepad is not connected");
					ImGui::PopID();
				}
			}
			else
			{
				ImGui::PushID("TXT" + index);
				ImGui::Text("Not controlled by gamepad");
				ImGui::PopID();
			}
		}
	}
	ImGui::End();
}
