#pragma once
#include "Component.h"
#include "GameEvent.h"

namespace dae
{
	class Health final : public Component
	{
	public:
		struct OnHealthChanged final : public GameEvent
		{
			OnHealthChanged() = delete;
			explicit OnHealthChanged(Health* component, int delta) 
				: GameEvent("OnHealthChanged", true), Delta{delta}, HealthComponent{component}
			{
			}

			const Health* HealthComponent;
			const int Delta;
		};

		struct OnDeath final : public GameEvent
		{
			OnDeath() = delete;
			explicit OnDeath(Health* deadComponent) :GameEvent("OnDeath", true), HealthComponent{ deadComponent } {}

			const Health* HealthComponent;
		};

		Health(GameObject* owner) : Component(owner) 
		{
		}
		Health(int maxHP, GameObject* owner) : Component(owner), m_MaxHealthPoints{ maxHP }
		{
		}
		~Health() = default;
		
		Health(const Health&) 					= delete;
		Health(Health&&) noexcept 				= delete;
		Health& operator=(const Health&) 	 	= delete;
		Health& operator=(Health&&) noexcept 	= delete;

		int GetHealth() const { return m_CurrentHealth; }

		void ApplyHealth(int HP)
		{
			if (m_Immune)
				return;
			m_Immune = HP < 0;

			m_CurrentHealth += HP;
			m_CurrentHealth %= (m_MaxHealthPoints + 1);

			// static game event function
			GameEvent::Dispatch<OnHealthChanged>(this, HP);;

			if (m_CurrentHealth <= 0)
				GameEvent::Dispatch<OnDeath>(this);
		}

		void ChangeMaxHP(int HP)
		{
			m_MaxHealthPoints = HP;
			ResetHP();
		}

		void ResetHP()
		{
			int delta{ m_MaxHealthPoints - m_CurrentHealth };
			ApplyHealth(delta);
		}

		void ResetImmunity()
		{
			m_Immune = false;
		}

	private:
		int m_MaxHealthPoints{ 4 };
		int m_CurrentHealth{ m_MaxHealthPoints };
		bool m_Immune{};
	};
}