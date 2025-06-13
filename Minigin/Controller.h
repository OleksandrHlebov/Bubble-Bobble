#pragma once
#include "Component.h"
#include "InputManager.h"
#include <memory>

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

		Gamepad* GetGamepad() { return m_Gamepad.get(); }

		uint32_t GetPlayerIndex() { return m_PlayerIndex; };

	protected:
		Controller(GameObject* owner, bool usesGamepad = false);

	private:
		std::unique_ptr<Gamepad> m_Gamepad{};

		uint32_t m_PlayerIndex;
	};
}