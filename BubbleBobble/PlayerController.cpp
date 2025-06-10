#include "PlayerController.h"
#include "InputManager.h"
#include "MovementCommands.h"
#include "DamageCommand.h"
#include "JumpCommand.h"
#include "PlayerState.h"
#include "Health.h"
#include "DyingPlayerState.h"
#include "BurpCommand.h"
#include "BurpPlayerState.h"
#include "SDL_scancode.h"

dae::PlayerController::PlayerController(bool useGamepad, GameObject* owner)
	: Controller(owner, useGamepad)
	, m_PlayerState{ std::make_unique<PlayerState>(owner) } 
	{}

dae::PlayerController::PlayerController(GameObject* owner) : PlayerController(true, owner)
{
}

dae::PlayerController::~PlayerController() {}

void dae::PlayerController::Start()
{
	InputManager& inputManager = InputManager::GetInstance();
	
	const bool usingGamepad{ GetGamepad() != nullptr };

	Keybind moveRight	{ (usingGamepad) ? Keybind(Gamepad::Button::DPadRight)	: Keybind(SDL_SCANCODE_D) };
	Keybind moveLeft	{ (usingGamepad) ? Keybind(Gamepad::Button::DPadLeft)	: Keybind(SDL_SCANCODE_A) };
	Keybind damageSelf	{ (usingGamepad) ? Keybind(Gamepad::Button::B)			: Keybind(SDL_SCANCODE_C) };
	Keybind burp		{ (usingGamepad) ? Keybind(Gamepad::Button::X)			: Keybind(SDL_SCANCODE_Z) };
	Keybind jump		{ (usingGamepad) ? Keybind(Gamepad::Button::A)			: Keybind(SDL_SCANCODE_X) };

	m_IAMoveRight	= inputManager.CreateInputAction<MoveCommand>(moveRight, BindTrigger::Held, GetControlledObject(), glm::vec3{  1.f, .0f, .0f });
	m_IAMoveLeft	= inputManager.CreateInputAction<MoveCommand>(moveLeft, BindTrigger::Held, GetControlledObject(), glm::vec3{ -1.f, .0f, .0f });

	m_IADamageSelf	= inputManager.CreateInputAction<DamageCommand>(damageSelf, BindTrigger::Pressed, GetControlledObject(), 1);
	m_IABurp		= inputManager.CreateInputAction<BurpCommand>(burp, BindTrigger::Pressed, GetControlledObject());
	m_IAJump		= inputManager.CreateInputAction<JumpCommand>(jump, BindTrigger::Released, GetControlledObject());

	if (usingGamepad)
		m_IAMoveRightLeft	= inputManager.CreateInputAction<MoveCommand>(Gamepad::ValueProvider::LeftThumbX, BindTrigger::Held, GetControlledObject(), glm::vec3{ 1.f,  .0f, .0f });

	GameEvent::Bind("OnDeath",
					[this](GameEvent* event)
					{
						Health::OnDeath* onDeath = static_cast<Health::OnDeath*>(event);
						if (onDeath->HealthComponent->GetOwner() == this->GetOwner())
						{
							PlayerState::TransitionState(m_PlayerState, std::make_unique<DyingPlayerState>(this->GetOwner()));
						}
					});
	GameEvent::Bind("OnBurp",
					[this](GameEvent* event)
					{
						OnBurp* onBurp = static_cast<OnBurp*>(event);
						if (onBurp->Object == this->GetOwner())
						{
							PlayerState::TransitionState(m_PlayerState, std::make_unique<BurpPlayerState>(this->GetOwner()));
						}
					});
}

void dae::PlayerController::Update(float deltaTime)
{
	if (std::unique_ptr<PlayerState> state = m_PlayerState->Update(deltaTime))
	{
		PlayerState::TransitionState(m_PlayerState, std::move(state));
	}
}

void dae::PlayerController::End()
{
	m_PlayerState->OnExit();
}
