#pragma once
#include "Component.h"
#include "EventDispatcher.h"

namespace dae
{
	struct GameEvent;
	class HealthDisplay final : public Component
	{
	public:
		HealthDisplay() = delete;
		HealthDisplay(GameObject* owner) : Component(owner) 
		{
		}
		~HealthDisplay() = default;

		HealthDisplay(const HealthDisplay&) = delete;
		HealthDisplay(HealthDisplay&&) noexcept = delete;
		HealthDisplay& operator=(const HealthDisplay&) = delete;
		HealthDisplay& operator=(HealthDisplay&&) noexcept = delete;

		void TrackHealth(Component* health);
		void TrackHealth(GameObject* gameObject);

		void HandleHealthChange(GameEvent* gameEvent);
		void HandleDeath(GameEvent* gameEvent);

		void End() override;

	private:
		void Start();
		void DisplayHealth();

		EventHandler m_HealthChangeHandler{ std::bind(&HealthDisplay::HandleHealthChange, this, std::placeholders::_1) };
		EventHandler m_DeathHandler{ std::bind(&HealthDisplay::HandleDeath, this, std::placeholders::_1) };

		Component* m_Health;
		int m_DisplayedHealth{ -1 };
	};
}