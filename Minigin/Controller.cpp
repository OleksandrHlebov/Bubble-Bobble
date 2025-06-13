#include "Controller.h"
#include "Scene.h"

dae::Controller::Controller(GameObject* owner, bool usesGamepad /*= false*/) 
	: Component(owner)
	, m_PlayerIndex{ GetOwner()->GetScene()->AddPlayer() }
{
	if (usesGamepad)
	{
		m_Gamepad = std::make_unique<Gamepad>();
		InputManager::GetInstance().AddGamepad(m_Gamepad.get());
	}
}
