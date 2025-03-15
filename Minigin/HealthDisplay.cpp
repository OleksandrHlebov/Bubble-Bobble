#include "HealthDisplay.h"
#include "Health.h"
#include "TextComponent.h"
#include "GameObject.h"
#include <iostream>

void dae::HealthDisplay::TrackHealth(Component* health)
{
	Health* temp = dynamic_cast<Health*>(health);
	if (!temp)
	{
		std::cerr << "invalid health component to track\n";
		return;
	}
	m_Health = health;
	m_DisplayedHealth = temp->GetHealth();
	DisplayHealth();
}

void dae::HealthDisplay::TrackHealth(GameObject* gameObject)
{
	Health* healthComponent = gameObject->GetComponent<Health>();
	TrackHealth(healthComponent);
}

void dae::HealthDisplay::HandleHealthChange(GameEvent* gameEvent)
{
	if (auto onHealthChanged = dynamic_cast<const Health::OnHealthChanged*>(gameEvent))
	{
		if (onHealthChanged->HealthComponent == m_Health)
		{
			m_DisplayedHealth = onHealthChanged->HealthComponent->GetHealth();
			DisplayHealth();
		}
	}
}

void dae::HealthDisplay::HandleDeath(GameEvent* gameEvent)
{
	if (auto onDeath = dynamic_cast<const Health::OnDeath*>(gameEvent))
	{
		if (onDeath->HealthComponent == m_Health)
		{
			TextComponent* textComp = GetOwner()->GetComponent<TextComponent>();
			if (!textComp)
			{
				std::cerr << "Missing text component in health display";
				return;
			}
			textComp->SetText("Health: DEAD");
		}
	}
}

void dae::HealthDisplay::Start()
{
	using namespace std::placeholders;
	GameEvent::Bind("OnHealthChanged", std::bind(&HealthDisplay::HandleHealthChange, this, _1));
	GameEvent::Bind("OnDeath", std::bind(&HealthDisplay::HandleDeath, this, _1));
}

void dae::HealthDisplay::DisplayHealth()
{
	TextComponent* textComp = GetOwner()->GetComponent<TextComponent>();
	if (!textComp)
	{
		std::cerr << "Missing text component in health display";
		return;
	}
	textComp->SetText("Health: " + std::to_string(m_DisplayedHealth));
}
