#include "KeyboardPlayerController.h"
#include "InputManager.h"
#include "MovementCommands.h"
#include <SDL_scancode.h>

dae::KeyboardPlayerController::KeyboardPlayerController(GameObject* owner) : Controller(owner) {}

dae::KeyboardPlayerController::~KeyboardPlayerController() {}

void dae::KeyboardPlayerController::Start()
{
	m_IAMoveUp		= InputManager::GetInstance().CreateInputAction<Move::Up>(GetControlledObject(), SDL_SCANCODE_W, BindTrigger::Held);
	m_IAMoveDown	= InputManager::GetInstance().CreateInputAction<Move::Down>(GetControlledObject(), SDL_SCANCODE_S, BindTrigger::Held);
	m_IAMoveRight	= InputManager::GetInstance().CreateInputAction<Move::Right>(GetControlledObject(), SDL_SCANCODE_D, BindTrigger::Held);
	m_IAMoveLeft	= InputManager::GetInstance().CreateInputAction<Move::Left>(GetControlledObject(), SDL_SCANCODE_A, BindTrigger::Held);
}



