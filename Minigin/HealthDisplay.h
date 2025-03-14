#pragma once
#include "Component.h"

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

		void HandleHealthChange(const GameEvent* gameEvent);
		void HandleDeath(const GameEvent* gameEvent);

	private:
		void Start();
		void DisplayHealth();

		Component* m_Health;
		int m_DisplayedHealth{ -1 };
	};
}