#include "KeyboardPlayerController.h"
#include "InputManager.h"
#include "MovementCommands.h"
#include <SDL_scancode.h>
#include "DamageCommand.h"
#include "PickUpCommand.h"

dae::KeyboardPlayerController::KeyboardPlayerController(GameObject* owner) : Controller(owner) {}

dae::KeyboardPlayerController::~KeyboardPlayerController() {}

void dae::KeyboardPlayerController::Start()
{
	InputManager& inputManager = InputManager::GetInstance();
	m_IAMoveUp		= inputManager.CreateInputAction<MoveCommand>(SDL_SCANCODE_W, BindTrigger::Held, GetControlledObject(), glm::vec3{  .0f, -1.f, .0f });
	m_IAMoveLeft	= inputManager.CreateInputAction<MoveCommand>(SDL_SCANCODE_A, BindTrigger::Held, GetControlledObject(), glm::vec3{ -1.f,  .0f, .0f });
	m_IAMoveDown	= inputManager.CreateInputAction<MoveCommand>(SDL_SCANCODE_S, BindTrigger::Held, GetControlledObject(), glm::vec3{  .0f,  1.f, .0f });
	m_IAMoveRight	= inputManager.CreateInputAction<MoveCommand>(SDL_SCANCODE_D, BindTrigger::Held, GetControlledObject(), glm::vec3{  1.f,  .0f, .0f });
	
	m_IADamageSelf	= inputManager.CreateInputAction<DamageCommand>(SDL_SCANCODE_C, BindTrigger::Pressed, GetControlledObject(), 1);
	m_IAPickUp		= inputManager.CreateInputAction<PickUpCommand>(SDL_SCANCODE_X, BindTrigger::Pressed, GetControlledObject());

}



