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
#include "Helpers.h"
#include "MenuNavigationCommand.h"
#include "PlayerInMenuState.h"
#include "MuteSoundCommand.h"
#include "NextSceneCommand.h"

dae::PlayerController::PlayerController(PlayerType&& type, bool useGamepad, GameObject* owner)
	: Controller(owner, useGamepad)
	, m_Type		{ std::move(type) }
	, m_PlayerState	{ std::make_unique<PlayerState>(m_Type, owner) } 
	{}

dae::PlayerController::PlayerController(bool useGamepad, GameObject* owner)
	: Controller(owner, useGamepad)
	, m_PlayerState{ std::make_unique<PlayerInMenuState>(m_Type, owner) }
{
	m_PlayerState->OnEnter();
}

dae::PlayerController::PlayerController(PlayerType&& type, GameObject* owner) : PlayerController(std::move(type), true, owner)
{
}

dae::PlayerController::~PlayerController() {}

void dae::PlayerController::Start()
{
	const bool usingGamepad{ GetGamepad() != nullptr };

	m_IAMute = CreateInputAction<MuteSoundCommand>(Keybind(SDL_SCANCODE_F2), BindTrigger::Pressed);
	m_IAMute = CreateInputAction<NextSceneCommand>(Keybind(SDL_SCANCODE_F1), BindTrigger::Pressed);

	Keybind moveRight	{ (usingGamepad) ? Keybind(Gamepad::Button::DPadRight)	: Keybind(SDL_SCANCODE_D) };
	Keybind moveLeft	{ (usingGamepad) ? Keybind(Gamepad::Button::DPadLeft)	: Keybind(SDL_SCANCODE_A) };
	Keybind moveUp		{ (usingGamepad) ? Keybind(Gamepad::Button::DPadUp)		: Keybind(SDL_SCANCODE_W) };
	Keybind moveDown	{ (usingGamepad) ? Keybind(Gamepad::Button::DPadDown)	: Keybind(SDL_SCANCODE_S) };
	Keybind damageSelf	{ (usingGamepad) ? Keybind(Gamepad::Button::B)			: Keybind(SDL_SCANCODE_C) };
	Keybind burp		{ (usingGamepad) ? Keybind(Gamepad::Button::X)			: Keybind(SDL_SCANCODE_Z) };
	Keybind jump		{ (usingGamepad) ? Keybind(Gamepad::Button::A)			: Keybind(SDL_SCANCODE_X) };

	m_IAMoveRight	= CreateInputAction<MoveCommand>(moveRight, BindTrigger::Held, GetControlledObject(), glm::vec3{  1.f, .0f, .0f });
	m_IAMoveLeft	= CreateInputAction<MoveCommand>(moveLeft, BindTrigger::Held, GetControlledObject(), glm::vec3{ -1.f, .0f, .0f });

	m_IADamageSelf	= CreateInputAction<DamageCommand>(damageSelf, BindTrigger::Pressed, GetControlledObject(), 1);
	m_IABurp		= CreateInputAction<BurpCommand>(burp, BindTrigger::Pressed, GetControlledObject());
	m_IAJump		= CreateInputAction<JumpCommand>(jump, BindTrigger::Pressed, GetControlledObject());

	m_IAMenuLeft	= CreateInputAction<MenuNavigationCommand>(moveLeft, BindTrigger::Pressed, GetControlledObject(), glm::ivec3{ -1, 0, 0 });
	m_IAMenuRight	= CreateInputAction<MenuNavigationCommand>(moveRight, BindTrigger::Pressed, GetControlledObject(), glm::ivec3{ 1, 0, 0 });
	m_IAMenuUp		= CreateInputAction<MenuNavigationCommand>(moveUp, BindTrigger::Pressed, GetControlledObject(), glm::ivec3{ 0, -1, 0 });
	m_IAMenuDown	= CreateInputAction<MenuNavigationCommand>(moveDown, BindTrigger::Pressed, GetControlledObject(), glm::ivec3{ 0, 1, 0 });
	m_IAMenuPress	= CreateInputAction<MenuNavigationCommand>(jump, BindTrigger::Pressed, GetControlledObject(), glm::ivec3{ 0, 0, 1 });

	GameEvent::Bind("OnHealthChanged", &m_HealthChangedHandler);
}

void dae::PlayerController::Update(float deltaTime)
{
	if (std::unique_ptr<PlayerState> state = m_PlayerState->Update(deltaTime))
	{
		dae::TransitionState(m_PlayerState, std::move(state));
	}
}

void dae::PlayerController::End()
{
	GameEvent::UnBind("OnHealthChanged", &m_HealthChangedHandler);
	m_PlayerState->OnExit();
	m_IAMoveRight->Delete();
	m_IAMoveLeft->Delete();
	m_IADamageSelf->Delete();
	m_IABurp->Delete();
	m_IAJump->Delete();
	m_IAMenuLeft->Delete();
	m_IAMenuRight->Delete();
	m_IAMenuUp->Delete();
	m_IAMenuDown->Delete();
	m_IAMenuPress->Delete();
}

void dae::PlayerController::Attack()
{
	dae::TransitionState<PlayerState>(m_PlayerState, std::make_unique<BurpPlayerState>(m_Type, this->GetOwner()));
}

void dae::PlayerController::HandleHealthChange(GameEvent* event)
{
	Health::OnHealthChanged* onHealthChanged = static_cast<Health::OnHealthChanged*>(event);
	if (onHealthChanged->HealthComponent->GetOwner() == this->GetOwner() && onHealthChanged->Delta < 0)
	{
		m_PlayerState->ForceAllowTransition();
		dae::TransitionState<PlayerState>(m_PlayerState, std::make_unique<DyingPlayerState>(m_Type, this->GetOwner()));
	}
}
