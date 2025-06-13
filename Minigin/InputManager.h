#pragma once
#include "Singleton.h"
#include <memory>
#include <list>
#include <array>
#include "Gamepad.h"
#include "InputAction.h"

namespace dae
{
	class GameObject;
	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();
		~InputManager();

		bool ProcessInput(float deltaTime);
		
		size_t GetGamepadCount();
		Gamepad* GetGamepadByPlayerIndex(uint32_t index);
		Gamepad* GetFirstAvailableGamepad();

		void RemoveInputAction(InputAction* inputAction);

		template<typename CommandType>
		InputAction* CreateInputAction(Keybind keybind, BindTrigger trigger)
		{
			auto& action = m_InputActions.emplace_back(new CommandType(), keybind, trigger);
			return &action;
		}

		template<typename GameObjectCommandType, typename... Args>
		InputAction* CreateInputAction(Keybind keybind, BindTrigger trigger, GameObject* object, Args&&... constructorParams)
		{
			auto& action = m_InputActions.emplace_back(new GameObjectCommandType(object, std::forward<Args>(constructorParams)...), keybind, trigger);
			return &action;
		}

	private:
		template<typename ValueType>
		float ToPercentOfMax(ValueType value)
		{
			return static_cast<float>(value) / std::numeric_limits<ValueType>::max();
		}

		void ExecuteValue(InputAction& inputAction, float currentValue, float previousValue, float deltaTime)
		{
			if (previousValue == 0 && currentValue != 0)
				inputAction.Execute(BindTrigger::Pressed, deltaTime);
			if (currentValue != 0)
				inputAction.Execute(BindTrigger::Held, deltaTime);
			if (previousValue != 0 && currentValue == 0)
				inputAction.Execute(BindTrigger::Released, deltaTime);
		}

		// list to not invalidate references on push back
		std::list<InputAction> m_InputActions;

		inline static const int GAMEPADS_SUPPORTED{ 4 };

		std::array<Gamepad, GAMEPADS_SUPPORTED> m_Gamepads;
	};
}
