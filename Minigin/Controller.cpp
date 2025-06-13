#include "Controller.h"
#include "Scene.h"

dae::Controller::Controller(GameObject* owner, bool usesGamepad /*= false*/) 
	: Component(owner)
	, m_PlayerIndex{ GetOwner()->GetScene()->AddPlayer() }
{
	if (usesGamepad)
	{
		if (Gamepad* gamepad = InputManager::GetInstance().GetGamepadByPlayerIndex(m_PlayerIndex))
		{
			m_Gamepad = gamepad;
			return;
		}
		m_Gamepad = InputManager::GetInstance().GetFirstAvailableGamepad();
		m_Gamepad->AssignToPlayer(m_PlayerIndex);
	}
}
