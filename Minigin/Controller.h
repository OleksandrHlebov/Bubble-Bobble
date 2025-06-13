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

		Gamepad* GetGamepad() { return m_Gamepad; }

		uint32_t GetPlayerIndex() { return m_PlayerIndex; };

		template<typename CommandType>
		InputAction* CreateInputAction(Keybind keybind, BindTrigger trigger)
		{
			InputAction* ia = InputManager::GetInstance().CreateInputAction<CommandType>(keybind, trigger);
			if (m_Gamepad)
				ia->LinkToDeviceIndex(m_Gamepad->GetDeviceIndex());
			return ia;
		}

		template<typename GameObjectCommandType, typename... Args>
		InputAction* CreateInputAction(Keybind keybind, BindTrigger trigger, GameObject* object, Args&&... constructorParams)
		{
			InputAction* ia = InputManager::GetInstance().CreateInputAction<GameObjectCommandType>(keybind, trigger, object, std::forward<Args>(constructorParams)...);
			if (m_Gamepad)
				ia->LinkToDeviceIndex(m_Gamepad->GetDeviceIndex());
			return ia;
		}

	protected:
		Controller(GameObject* owner, bool usesGamepad = false);

	private:
		Gamepad* m_Gamepad{};

		uint32_t m_PlayerIndex;
	};
}