#include "InputAction.h"
#include "InputManager.h"

dae::InputAction::InputAction(Command* command, Keybind keybind, BindTrigger trigger) : m_Keybind{ keybind }
{
	m_TriggerBinds[trigger].reset(command);
}

void dae::InputAction::Bind(Command* command, BindTrigger trigger)
{
	m_TriggerBinds[trigger].reset(command);
}

void dae::InputAction::UnBind(BindTrigger trigger)
{
	m_TriggerBinds[trigger].reset(nullptr);
}

void dae::InputAction::Delete()
{
	InputManager::GetInstance().RemoveInputAction(this);
}

void dae::InputAction::Execute(BindTrigger trigger, float deltaTime)
{
	if (m_TriggerBinds[trigger])
	{
		m_TriggerBinds[trigger]->Execute(deltaTime);
	}
}
