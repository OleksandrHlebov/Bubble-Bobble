#include "MenuComponent.h"
#include "Scene.h"
#include "GameObject.h"
#include "TextComponent.h"

void dae::MenuComponent::AddButton(const std::string& label, std::function<void(GameObject*, const glm::ivec2&)> inputHandler)
{
	SDL_Color& currentColor{ (m_ButtonObjects.empty()) ? m_SelectedColor : m_InActiveColor };
	GameObject* parent = (m_ButtonObjects.empty()) ? GetOwner() : m_ButtonObjects.back();
	m_Delegates.emplace_back(inputHandler);
	m_ButtonObjects.emplace_back(GetOwner()->GetScene()->CreateGameObject());
	GameObject* button = m_ButtonObjects.back();
	button->AttachTo(parent);
	button->SetLocalPosition(glm::vec3{ (m_IsHorizontal) * m_Margin, (!m_IsHorizontal) * m_Margin, .0f });
	button->AddComponent<Render2DComponent>();
	auto textComp = button->AddComponent<TextComponent>(m_Font);
	textComp->SetText(label);
	textComp->SetColor(currentColor);
}

void dae::MenuComponent::ProcessInput(const glm::ivec3& input)
{
	int increment{ (m_IsHorizontal) ? input.x : input.y };

	if (increment)
	{
		GameObject* prevButton = m_ButtonObjects[m_SelectedIndex];
		prevButton->GetComponent<TextComponent>()->SetColor(m_InActiveColor);

		m_SelectedIndex += increment;
		if (m_SelectedIndex < 0)
			m_SelectedIndex = static_cast<int>(std::ssize(m_Delegates) - 1);
		m_SelectedIndex %= std::ssize(m_Delegates);

		GameObject* nextButton = m_ButtonObjects[m_SelectedIndex];
		nextButton->GetComponent<TextComponent>()->SetColor(m_SelectedColor);

		return;
	}

	m_Delegates[m_SelectedIndex](m_ButtonObjects[m_SelectedIndex], {((m_IsHorizontal) ? input.y : input.x), input.z});
}
