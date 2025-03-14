#pragma once
#include "Component.h"

namespace dae
{
	class PickUpComponent final : public Component
	{
	public:
		PickUpComponent() = delete;
		PickUpComponent(float radius, GameObject* owner) : Component(owner), Radius{ radius }
		{
		}
		~PickUpComponent() = default;
		
		PickUpComponent(const PickUpComponent&) 				= delete;
		PickUpComponent(PickUpComponent&&) noexcept 			= delete;
		PickUpComponent& operator=(const PickUpComponent&) 	 	= delete;
		PickUpComponent& operator=(PickUpComponent&&) noexcept 	= delete;

		float Radius;

		void PickUp();

	private:

	};
}