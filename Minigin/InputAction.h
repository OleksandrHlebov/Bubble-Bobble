#pragma once
#include "Command.h"
#include "GameObject.h"
#include <memory>
#include "SDL_scancode.h"

namespace dae
{
	// own keybind implementation to allow
	// adjusting and remapping for other os
	enum class GamepadKey : uint32_t
	{
		DPadUp			= 0x0001,
		DPadDown		= 0x0002,
		DPadLeft		= 0x0004,
		DPadRight		= 0x0008,
		Start			= 0x0010,
		Back			= 0x0020,
		LeftThumb		= 0x0040,
		RightThumb		= 0x0080,
		LeftShoulder	= 0x0100,
		RightShoulder	= 0x0200,
		A				= 0x1000,
		B				= 0x2000,
		X				= 0x4000,
		Y				= 0x8000
	};
	
	struct Keybind
	{
		Keybind() = default;
		Keybind(GamepadKey gamepadKey) : Gamepad{ gamepadKey }
		{ }
		Keybind(SDL_Scancode scancode) : Keyboard{ scancode }
		{}

		GamepadKey	 Gamepad { 0 };
		SDL_Scancode Keyboard{ SDL_SCANCODE_UNKNOWN };
	};

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

		void ExecutePressed(float deltaTime)	{ if (m_PressedPtr)	 m_PressedPtr->Execute(m_Object, deltaTime);	}
		void ExecuteHeld(float deltaTime)		{ if (m_HeldPtr)	 m_HeldPtr->Execute(m_Object, deltaTime);		}
		void ExecuteReleased(float deltaTime)	{ if (m_ReleasedPtr) m_ReleasedPtr->Execute(m_Object, deltaTime);	}

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