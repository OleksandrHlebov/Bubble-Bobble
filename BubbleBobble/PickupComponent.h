#pragma once
#include "Component.h"
#include "GameEvent.h"

namespace dae
{
	class PickupComponent final : public Component
	{
	public:
		struct OnPickup final : public GameEvent
		{
			explicit OnPickup(GameObject* player, int value)
				: GameEvent("OnPickup", true)
				, Player	{ player }
				, Value		{ value }
				{}

			GameObject* const Player;
			const int Value;
		};
		PickupComponent() = delete;
		PickupComponent(int value, GameObject* owner)
			: Component(owner)
			, m_Value{ value }
			{}
		~PickupComponent() = default;
		
		PickupComponent(const PickupComponent&) 				= delete;
		PickupComponent(PickupComponent&&) noexcept 			= delete;
		PickupComponent& operator=(const PickupComponent&) 	 	= delete;
		PickupComponent& operator=(PickupComponent&&) noexcept 	= delete;

		void Start() override;

		void End() override;

		void HandleOverlap(GameEvent*);

	private:
		EventHandler m_OverlapHandler{ std::bind(&PickupComponent::HandleOverlap, this, std::placeholders::_1) };
		int m_Value;

	};
}