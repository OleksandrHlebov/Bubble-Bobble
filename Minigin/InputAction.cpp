#include "InputAction.h"
#include "InputManager.h"

dae::InputAction::InputAction(Command* command, Keybind keybind, BindTrigger trigger) : m_Keybind{ keybind }
{
	command->Initialize(this);
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

void dae::InputAction::Bind(Command* command, BindTrigger trigger)
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

void dae::InputAction::UnBind(BindTrigger trigger)
{
	switch (trigger)
	{
	case BindTrigger::Pressed:
		m_PressedPtr.reset(nullptr);
		break;
	case BindTrigger::Held:
		m_HeldPtr.reset(nullptr);
		break;
	case BindTrigger::Released:
		m_ReleasedPtr.reset(nullptr);
		break;
	}
}

void dae::InputAction::Delete()
{
	InputManager::GetInstance().RemoveInputAction(this);
}

void dae::InputAction::ExecutePressed(float deltaTime, float value /*= 1.f*/)
{
	if (m_PressedPtr)	 
	{
		m_DeltaTime = deltaTime;
		m_Value = value;
		m_PressedPtr->Execute();
	}
}

void dae::InputAction::ExecuteHeld(float deltaTime, float value /*= 1.f*/)
{
	if (m_HeldPtr)	 
	{
		m_DeltaTime = deltaTime;
		m_Value = value;
		m_HeldPtr->Execute();
	}
}

void dae::InputAction::ExecuteReleased(float deltaTime, float value /*= 1.f*/)
{
	if (m_ReleasedPtr) 
	{
		m_DeltaTime = deltaTime;
		m_Value = value;
		m_ReleasedPtr->Execute();
	}
}
