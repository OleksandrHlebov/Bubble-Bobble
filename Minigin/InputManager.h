#pragma once
#include "Singleton.h"
#include <memory>
#include <list>
#include <vector>
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

		void Init();

		bool ProcessInput(float deltaTime);
		
		size_t GetGamepadCount();
		Gamepad* GetGamepadByIndex(uint32_t index);

		void AddGamepad(Gamepad* gamepad);

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


		std::vector<Gamepad*> m_Gamepads;
	};
}
