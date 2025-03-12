#include "GamepadPlayerController.h"
#include "InputManager.h"
#include "MovementCommands.h"

dae::GamepadPlayerController::GamepadPlayerController(GameObject* owner) : Controller(owner) { InputManager::GetInstance().AddGamepad(&m_Gamepad); }

dae::GamepadPlayerController::~GamepadPlayerController() {}

void dae::GamepadPlayerController::Start()
{
	m_IAMoveUp		= InputManager::GetInstance().CreateInputAction<MoveCommand>(Gamepad::Button::DPadUp 
					 														   | Gamepad::Button::Y			, BindTrigger::Held, GetControlledObject(), glm::vec3{ .0f, -1.f, .0f });
	m_IAMoveDown	= InputManager::GetInstance().CreateInputAction<MoveCommand>(Gamepad::Button::DPadDown	, BindTrigger::Held, GetControlledObject(), glm::vec3{ .0f,  1.f, .0f });
	m_IAMoveRight	= InputManager::GetInstance().CreateInputAction<MoveCommand>(Gamepad::Button::DPadRight	, BindTrigger::Held, GetControlledObject(), glm::vec3{  1.f, .0f, .0f });
	m_IAMoveLeft	= InputManager::GetInstance().CreateInputAction<MoveCommand>(Gamepad::Button::DPadLeft	, BindTrigger::Held, GetControlledObject(), glm::vec3{ -1.f, .0f, .0f });

	m_IAMoveRightLeft	= InputManager::GetInstance().CreateInputAction<MoveCommand>(Keybind{ Gamepad::ValueProvider::LeftThumbX, Gamepad::Button::X }, BindTrigger::Held, GetControlledObject(), glm::vec3{ 1.f, .0f, .0f });
	m_IAMoveUpDown		= InputManager::GetInstance().CreateInputAction<MoveCommand>(Gamepad::ValueProvider::LeftThumbY, BindTrigger::Held, GetControlledObject(), glm::vec3{ .0f, -1.f, .0f });

	//m_IAMoveRightLeft	= InputManager::GetInstance().CreateInputAction<Move::LeftRight>(GetControlledObject(), Gamepad::ValueProvider::LeftThumbX, BindTrigger::Held);
	//m_IAMoveUpDown		= InputManager::GetInstance().CreateInputAction<Move::UpDown>(GetControlledObject(), Gamepad::ValueProvider::LeftThumbY, BindTrigger::Held);
}
