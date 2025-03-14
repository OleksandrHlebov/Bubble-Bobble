#pragma once
#include "Component.h"

namespace dae
{
	class PelletComponent final : public Component
	{
	public:
		PelletComponent() = delete;
		PelletComponent(GameObject* owner, int value) : Component(owner), m_Value{ value }
		{
		}
		~PelletComponent() = default;
		
		PelletComponent(const PelletComponent&) 				= delete;
		PelletComponent(PelletComponent&&) noexcept 			= delete;
		PelletComponent& operator=(const PelletComponent&) 	 	= delete;
		PelletComponent& operator=(PelletComponent&&) noexcept 	= delete;

		void PickUp(GameObject* instigator);

	private:
		int m_Value;

	};
}