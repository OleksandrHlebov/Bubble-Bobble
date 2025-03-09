#pragma once
#include "Command.h"
#include "GameObject.h"
#include <memory>
#include <any>
#include "Keybind.h"

namespace dae
{
	enum class BindTrigger : uint8_t
	{
		Pressed,
		Held,
		Released
	};

	class InputAction final
	{
	public:
		InputAction(GameObject* object, Command* command, Keybind keybind, BindTrigger trigger) 
			: m_Keybind{ keybind }, m_Object{ object }
		{
			switch (trigger)
			{
			case BindTrigger::Pressed:
				m_PressedPtr.reset(command);
				break;
			case BindTrigger::Held:
				m_HeldPtr.reset(command);
				break;
			case BindTrigger::Released:
				m_ReleasedPtr.reset(command);
				break;
			}
		}
		~InputAction() = default;

		InputAction(const InputAction&) = delete;
		InputAction(InputAction&&) noexcept = delete;
		InputAction& operator=(const InputAction&) = delete;
		InputAction& operator=(InputAction&&) noexcept = delete;

		void Bind(Command* command, BindTrigger trigger)
		{
			switch (trigger)
			{
			case BindTrigger::Pressed:
				m_PressedPtr.reset(command);
				break;
			case BindTrigger::Held:
				m_HeldPtr.reset(command);
				break;
			case BindTrigger::Released:
				m_ReleasedPtr.reset(command);
				break;
			}
		}

		void ExecutePressed(float deltaTime, float value)	{ if (m_PressedPtr)	 m_PressedPtr->Execute(m_Object, value, deltaTime);	}
		void ExecuteHeld(float deltaTime, float value)		{ if (m_HeldPtr)	 m_HeldPtr->Execute(m_Object, value, deltaTime);			}
		void ExecuteReleased(float deltaTime, float value)	{ if (m_ReleasedPtr) m_ReleasedPtr->Execute(m_Object, value, deltaTime);		}

		Keybind GetKeybind()
		{
			return m_Keybind;
		}

	private:
		std::unique_ptr<Command> m_PressedPtr	{};
		std::unique_ptr<Command> m_HeldPtr		{};
		std::unique_ptr<Command> m_ReleasedPtr	{};
		Keybind m_Keybind{};
		GameObject* m_Object;
	};
}