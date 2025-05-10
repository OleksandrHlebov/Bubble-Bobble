#pragma once
#include "Component.h"

namespace dae
{
	class BurpComponent final : public Component
	{
	public:
		BurpComponent(GameObject* owner) : Component(owner) {}
		~BurpComponent() = default;
		
		BurpComponent(const BurpComponent&) 				= delete;
		BurpComponent(BurpComponent&&) noexcept 			= delete;
		BurpComponent& operator=(const BurpComponent&) 	 	= delete;
		BurpComponent& operator=(BurpComponent&&) noexcept 	= delete;

	private:
		
	};
}