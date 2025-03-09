#include "GamepadPlayerController.h"
#include "InputManager.h"
#include "MovementCommands.h"

dae::GamepadPlayerController::GamepadPlayerController(GameObject* owner) : Controller(owner) { InputManager::GetInstance().AddGamepad(&m_Gamepad); }

dae::GamepadPlayerController::~GamepadPlayerController() {}

void dae::GamepadPlayerController::Start()
{
	m_IAMoveUp		= InputManager::GetInstance().CreateInputAction<Move::Up>(GetControlledObject(), Gamepad::Button::DPadUp, BindTrigger::Held);
	m_IAMoveDown	= InputManager::GetInstance().CreateInputAction<Move::Down>(GetControlledObject(), Gamepad::Button::DPadDown, BindTrigger::Held);
	m_IAMoveRight	= InputManager::GetInstance().CreateInputAction<Move::Right>(GetControlledObject(), Gamepad::Button::DPadRight, BindTrigger::Held);
	m_IAMoveLeft	= InputManager::GetInstance().CreateInputAction<Move::Left>(GetControlledObject(), Gamepad::Button::DPadLeft, BindTrigger::Held);
	
	m_IAMoveRightLeft	= InputManager::GetInstance().CreateInputAction<Move::LeftRight>(GetControlledObject(), Gamepad::ValueProvider::LeftThumbX, BindTrigger::Held);
	m_IAMoveUpDown		= InputManager::GetInstance().CreateInputAction<Move::UpDown>(GetControlledObject(), Gamepad::ValueProvider::LeftThumbY, BindTrigger::Held);
}
