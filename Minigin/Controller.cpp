#include "Controller.h"
#include "Scene.h"

dae::Controller::Controller(GameObject* owner, bool usesGamepad /*= false*/) 
	: Component(owner)
	, m_PlayerIndex{ (usesGamepad) ? GetOwner()->GetScene()->AddPlayer() : 0 }
{
	if (usesGamepad)
	{
		InputManager& inputManager = InputManager::GetInstance();
		if (Gamepad* gamepad = inputManager.GetGamepadByPlayerIndex(m_PlayerIndex))
		{
			m_Gamepad = gamepad;
			return;
		}
		m_Gamepad = inputManager.GetFirstAvailableGamepad();
		m_Gamepad->AssignToPlayer(m_PlayerIndex);
	}
}
