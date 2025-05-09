#include "KeyboardPlayerController.h"
#include "InputManager.h"
#include "MovementCommands.h"
#include <SDL_scancode.h>
#include "DamageCommand.h"
#include "PickUpCommand.h"
#include "JumpCommand.h"
#include "PlayerState.h"
#include "IdlePlayerState.h"
#include "Health.h"
#include "DyingPlayerState.h"

dae::KeyboardPlayerController::KeyboardPlayerController(GameObject* owner) 
		: Controller(owner) 
		, m_PlayerState{ std::make_unique<PlayerState>(owner) }
		{}

dae::KeyboardPlayerController::~KeyboardPlayerController() {}

void dae::KeyboardPlayerController::Start()
{
	InputManager& inputManager = InputManager::GetInstance();
	//m_IAMoveUp		= inputManager.CreateInputAction<MoveCommand>(SDL_SCANCODE_W, BindTrigger::Held, GetControlledObject(), glm::vec3{  .0f, -1.f, .0f });
	m_IAMoveLeft	= inputManager.CreateInputAction<MoveCommand>(SDL_SCANCODE_A, BindTrigger::Held, GetControlledObject(), glm::vec3{ -1.f,  .0f, .0f });
	//m_IAMoveDown	= inputManager.CreateInputAction<MoveCommand>(SDL_SCANCODE_S, BindTrigger::Held, GetControlledObject(), glm::vec3{  .0f,  1.f, .0f });
	m_IAMoveRight	= inputManager.CreateInputAction<MoveCommand>(SDL_SCANCODE_D, BindTrigger::Held, GetControlledObject(), glm::vec3{  1.f,  .0f, .0f });
	
	m_IADamageSelf	= inputManager.CreateInputAction<DamageCommand>(SDL_SCANCODE_C, BindTrigger::Pressed, GetControlledObject(), 1);

	m_IAJump = inputManager.CreateInputAction<JumpCommand>(SDL_SCANCODE_X, BindTrigger::Released, GetControlledObject());

	GameEvent::Bind("OnDeath", 
				[this](GameEvent* event) 
				{
					Health::OnDeath* onDeath = static_cast<Health::OnDeath*>(event);
					if (onDeath->HealthComponent->GetOwner() == this->GetOwner())
					{
						PlayerState::TransitionState(m_PlayerState, std::make_unique<DyingPlayerState>(this->GetOwner()));
					}
				});
}

void dae::KeyboardPlayerController::Update(float deltaTime)
{
	if (std::unique_ptr<PlayerState> state = m_PlayerState->Update(deltaTime))
	{
		PlayerState::TransitionState(m_PlayerState, std::move(state));
	}
}

void dae::KeyboardPlayerController::End()
{
	m_PlayerState->OnExit();
}

