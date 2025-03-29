#include "Controller.h"


dae::Controller::Controller(GameObject* owner, bool usesGamepad /*= false*/) : Component(owner)
{
	if (usesGamepad)
	{
		m_Gamepad = std::make_unique<Gamepad>();
		InputManager::GetInstance().AddGamepad(m_Gamepad.get());
	}
}
