#include "KeyboardPlayerController.h"
#include "InputManager.h"
#include "MovementCommands.h"
#include <SDL_scancode.h>

dae::KeyboardPlayerController::KeyboardPlayerController(GameObject* owner) : Controller(owner) {}

dae::KeyboardPlayerController::~KeyboardPlayerController() {}

void dae::KeyboardPlayerController::Start()
{
	m_IAMoveUp		= InputManager::GetInstance().CreateInputAction<MoveCommand>(SDL_SCANCODE_W, BindTrigger::Held, GetControlledObject(), glm::vec3{  .0f, -1.f, .0f });
	m_IAMoveLeft	= InputManager::GetInstance().CreateInputAction<MoveCommand>(SDL_SCANCODE_A, BindTrigger::Held, GetControlledObject(), glm::vec3{ -1.f,  .0f, .0f });
	m_IAMoveDown	= InputManager::GetInstance().CreateInputAction<MoveCommand>(SDL_SCANCODE_S, BindTrigger::Held, GetControlledObject(), glm::vec3{  .0f,  1.f, .0f });
	m_IAMoveRight	= InputManager::GetInstance().CreateInputAction<MoveCommand>(SDL_SCANCODE_D, BindTrigger::Held, GetControlledObject(), glm::vec3{  1.f,  .0f, .0f });
}



