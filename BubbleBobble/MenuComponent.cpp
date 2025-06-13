#include "MenuComponent.h"
#include "Scene.h"
#include "GameObject.h"
#include "TextComponent.h"

void dae::MenuComponent::AddButton(const std::string& label, std::function<void(const glm::ivec2&)> inputHandler)
{
	m_Delegates.push_back(inputHandler);
	SDL_Color& currentColor{ (m_ButtonObjects.empty()) ? m_SelectedColor : m_InActiveColor };
	GameObject* parent = (m_ButtonObjects.empty()) ? GetOwner() : m_ButtonObjects.back();
	m_Delegates.emplace_back(inputHandler);
	m_ButtonObjects.emplace_back(GetOwner()->GetScene()->CreateGameObject());
	GameObject* button = m_ButtonObjects.back();
	button->AttachTo(parent);
	button->AddComponent<Render2DComponent>();
	auto textComp = button->AddComponent<TextComponent>(m_Font);
	textComp->SetText(label);
	textComp->SetColor(currentColor);
}

void dae::MenuComponent::ProcessInput(const glm::ivec3& input)
{
	int increment{ (m_IsHorizontal) ? input.x : input.y };
	if (increment)
		return;

	m_Delegates[m_SelectedIndex]({ ((m_IsHorizontal) ? input.y : input.x), input.z });
}
