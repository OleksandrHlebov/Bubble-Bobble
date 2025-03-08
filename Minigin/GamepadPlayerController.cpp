#include "GamepadPlayerController.h"
#include "InputManager.h"
#include "MovementCommands.h"

dae::GamepadPlayerController::GamepadPlayerController(GameObject* owner) : Controller(owner), m_PlayerIndex{ m_PlayerCount++ } { InputManager::GetInstance().AddPlayer(); }

dae::GamepadPlayerController::~GamepadPlayerController() {}

void dae::GamepadPlayerController::Start()
{
	m_IAMoveUp		= InputManager::GetInstance().CreateInputAction<Move::Up>(GetControlledObject(), GamepadKey::DPadUp, BindTrigger::Held);
	m_IAMoveDown	= InputManager::GetInstance().CreateInputAction<Move::Down>(GetControlledObject(), GamepadKey::DPadDown, BindTrigger::Held);
	m_IAMoveRight	= InputManager::GetInstance().CreateInputAction<Move::Right>(GetControlledObject(), GamepadKey::DPadRight, BindTrigger::Held);
	m_IAMoveLeft	= InputManager::GetInstance().CreateInputAction<Move::Left>(GetControlledObject(), GamepadKey::DPadLeft, BindTrigger::Held);
}
