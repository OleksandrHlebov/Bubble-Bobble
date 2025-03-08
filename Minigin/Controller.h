#pragma once
#include "Component.h"
#include "InputManager.h"

namespace dae
{
	class GameObject;
	class Controller : public Component
	{
	public:
		virtual ~Controller() = default;
		
		Controller(const Controller&) 					= delete;
		Controller(Controller&&) noexcept 				= delete;
		Controller& operator=(const Controller&) 	 	= delete;
		Controller& operator=(Controller&&) noexcept 	= delete;

		GameObject* GetControlledObject() { return GetOwner(); }

	protected:
		Controller(GameObject* owner) : Component(owner)
		{  }

	private:
	};
}