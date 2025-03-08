#pragma once
#include "Command.h"

class InputAction final
{
public:
	InputAction(Command* command, uint32 keybindMask) :
		m_CommandPtr{ command },
		m_Keybind	{ keybindMask }
	{}
	~InputAction() = default;
	
	InputAction(const InputAction&) 				= delete;
	InputAction(InputAction&&) noexcept 			= delete;
	InputAction& operator=(const InputAction&) 	 	= delete;
	InputAction& operator=(InputAction&&) noexcept 	= delete;

	uint32 GetKeybind()
	{
		return m_Keybind;
	}

private:
	Command* m_CommandPtr{};
	uint32	 m_Keybind{};
};