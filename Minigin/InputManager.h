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
		// list to not invalidate references on push back
		std::list<InputAction> m_InputActions;

		class InputManagerImplementation;
		std::unique_ptr<InputManagerImplementation> m_ImplementationPtr;
		std::vector<Gamepad*> m_Gamepads;
	};
}
