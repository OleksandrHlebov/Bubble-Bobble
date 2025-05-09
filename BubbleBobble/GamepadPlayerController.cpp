#include "GamepadPlayerController.h"
#include "InputManager.h"
#include "MovementCommands.h"
#include "DamageCommand.h"
#include "PickUpCommand.h"
#include "JumpCommand.h"
#include "PlayerState.h"
#include "Health.h"
#include "DyingPlayerState.h"

dae::GamepadPlayerController::GamepadPlayerController(GameObject* owner) : Controller(owner, true), m_PlayerState{ std::make_unique<PlayerState>(owner) } {  }

dae::GamepadPlayerController::~GamepadPlayerController() {}

void dae::GamepadPlayerController::Start()
{
	InputManager& inputManager = InputManager::GetInstance();

	//m_IAMoveUp		= inputManager.CreateInputAction<MoveCommand>(Gamepad::Button::DPadUp 
								 							    //| Gamepad::Button::Y		, BindTrigger::Held, GetControlledObject(), glm::vec3{ .0f, -1.f, .0f });
	//m_IAMoveDown	= inputManager.CreateInputAction<MoveCommand>(Gamepad::Button::DPadDown	, BindTrigger::Held, GetControlledObject(), glm::vec3{ .0f,  1.f, .0f });
	m_IAMoveRight	= inputManager.CreateInputAction<MoveCommand>(Gamepad::Button::DPadRight, BindTrigger::Held, GetControlledObject(), glm::vec3{  1.f, .0f, .0f });
	m_IAMoveLeft	= inputManager.CreateInputAction<MoveCommand>(Gamepad::Button::DPadLeft	, BindTrigger::Held, GetControlledObject(), glm::vec3{ -1.f, .0f, .0f });

	m_IAMoveRightLeft	= inputManager.CreateInputAction<MoveCommand>(Gamepad::ValueProvider::LeftThumbX, BindTrigger::Held, GetControlledObject(), glm::vec3{ 1.f,  .0f, .0f });
	//m_IAMoveUpDown		= inputManager.CreateInputAction<MoveCommand>(Gamepad::ValueProvider::LeftThumbY, BindTrigger::Held, GetControlledObject(), glm::vec3{ .0f, -1.f, .0f });

	m_IADamageSelf  = inputManager.CreateInputAction<DamageCommand>(Gamepad::Button::X, BindTrigger::Pressed, GetControlledObject(), 1);

	m_IAJump = inputManager.CreateInputAction<JumpCommand>(Gamepad::Button::A, BindTrigger::Released, GetControlledObject());

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

void dae::GamepadPlayerController::Update(float deltaTime)
{
	if (std::unique_ptr<PlayerState> state = m_PlayerState->Update(deltaTime))
	{
		PlayerState::TransitionState(m_PlayerState, std::move(state));
	}
}

void dae::GamepadPlayerController::End()
{
	m_PlayerState->OnExit();
}
