#include "GamepadPlayerController.h"
#include "InputManager.h"
#include "MovementCommands.h"
#include "DamageCommand.h"
#include "PickUpCommand.h"

dae::GamepadPlayerController::GamepadPlayerController(GameObject* owner) : Controller(owner) { InputManager::GetInstance().AddGamepad(&m_Gamepad); }

dae::GamepadPlayerController::~GamepadPlayerController() {}

void dae::GamepadPlayerController::Start()
{
	InputManager& inputManager = InputManager::GetInstance();

	m_IAMoveUp		= inputManager.CreateInputAction<MoveCommand>(Gamepad::Button::DPadUp 
								 							    | Gamepad::Button::Y		, BindTrigger::Held, GetControlledObject(), glm::vec3{ .0f, -1.f, .0f });
	m_IAMoveDown	= inputManager.CreateInputAction<MoveCommand>(Gamepad::Button::DPadDown	, BindTrigger::Held, GetControlledObject(), glm::vec3{ .0f,  1.f, .0f });
	m_IAMoveRight	= inputManager.CreateInputAction<MoveCommand>(Gamepad::Button::DPadRight, BindTrigger::Held, GetControlledObject(), glm::vec3{  1.f, .0f, .0f });
	m_IAMoveLeft	= inputManager.CreateInputAction<MoveCommand>(Gamepad::Button::DPadLeft	, BindTrigger::Held, GetControlledObject(), glm::vec3{ -1.f, .0f, .0f });

	m_IAMoveRightLeft	= inputManager.CreateInputAction<MoveCommand>(Gamepad::ValueProvider::LeftThumbX, BindTrigger::Held, GetControlledObject(), glm::vec3{ 1.f,  .0f, .0f });
	m_IAMoveUpDown		= inputManager.CreateInputAction<MoveCommand>(Gamepad::ValueProvider::LeftThumbY, BindTrigger::Held, GetControlledObject(), glm::vec3{ .0f, -1.f, .0f });

	m_IADamageSelf  = inputManager.CreateInputAction<DamageCommand>(Gamepad::Button::X, BindTrigger::Pressed, GetControlledObject(), 1);
	m_IAPickUp		= inputManager.CreateInputAction<PickUpCommand>(Gamepad::Button::A, BindTrigger::Pressed, GetControlledObject());
}
