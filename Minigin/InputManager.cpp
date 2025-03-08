#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Xinput.h>
#include <iostream>
#include <vector>
#include "InputManager.h"
#include "ImguiRenderer.h"


class dae::InputManager::InputManagerImplementation final
{
public:
	InputManagerImplementation(std::list<InputAction>& actionList) : m_InputActions{ actionList }
	{ }
	~InputManagerImplementation() = default;

	InputManagerImplementation(const InputManagerImplementation&) = delete;
	InputManagerImplementation(InputManagerImplementation&&) noexcept = delete;
	InputManagerImplementation& operator=(const InputManagerImplementation&) = delete;
	InputManagerImplementation& operator=(InputManagerImplementation&&) noexcept = delete;

	void Init();

	bool ProcessInput(float deltaTime);
	void AddPlayer();

	InputAction* CreateInputAction(GameObject* object, Command* command, Keybind keybind, BindTrigger trigger);

private:
	std::list<InputAction>& m_InputActions;
	std::vector<SDL_Scancode> m_HeldKeys;

	XINPUT_STATE m_PreviousState;
	XINPUT_STATE m_CurrentState;
	int m_PlayerCount{ };
};

bool dae::InputManager::InputManagerImplementation::ProcessInput(float deltaTime)
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) 
		{
			for (InputAction& inputAction : m_InputActions)
			{
				if (e.key.keysym.scancode == inputAction.GetKeybind().Keyboard)
				{
					inputAction.ExecutePressed(deltaTime);
					m_HeldKeys.push_back(e.key.keysym.scancode);
				}
			}
		}
		if (e.type == SDL_KEYUP)
		{
			for (InputAction& inputAction : m_InputActions)
			{
				if (e.key.keysym.scancode == inputAction.GetKeybind().Keyboard)
				{
					inputAction.ExecuteReleased(deltaTime);
					m_HeldKeys.erase(std::remove(m_HeldKeys.begin(), m_HeldKeys.end(), e.key.keysym.scancode));
				}
			}
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {

		}
		// etc...

		ImguiRenderer::GetInstance().ProcessEvents(e);
	}

	const Uint8* state = SDL_GetKeyboardState(nullptr);
	for (InputAction& inputAction : m_InputActions)
	{
		if (state[inputAction.GetKeybind().Keyboard])
		{
			inputAction.ExecuteHeld(deltaTime);
			m_HeldKeys.push_back(e.key.keysym.scancode);
		}
	}

	for (int index{}; index < m_PlayerCount; ++index)
	{
		CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		DWORD dwResult = XInputGetState(index, &m_CurrentState);

		if (dwResult != ERROR_SUCCESS)
		{
			if (dwResult != ERROR_DEVICE_NOT_CONNECTED)
			{
				std::cerr << "Failed to get xinput state. Code: " << dwResult << '\n';
				return false;
			}
			else continue;
		}

		WORD buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
		WORD buttonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
		WORD buttonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
		WORD buttonsHeldThisFrame = m_CurrentState.Gamepad.wButtons;

		for (InputAction& inputAction : m_InputActions)
		{
			WORD keyMask = static_cast<WORD>(inputAction.GetKeybind().Gamepad);
			if (keyMask & buttonsPressedThisFrame)
				inputAction.ExecutePressed(deltaTime);
			if (keyMask & buttonsHeldThisFrame)
				inputAction.ExecuteHeld(deltaTime);
			if (keyMask & buttonsReleasedThisFrame)
				inputAction.ExecuteReleased(deltaTime);
		}
	}

	return true;
}

void dae::InputManager::InputManagerImplementation::Init()
{
	for (int index{}; index < m_PlayerCount; ++index)
	{
		CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		DWORD dwResult = XInputGetState(index, &m_CurrentState);
		if (dwResult != ERROR_SUCCESS)
		{
			if (dwResult == ERROR_DEVICE_NOT_CONNECTED)
			{
				std::cerr << "Controller " << index << " not connected\n";
			}
			else
			{
				std::cerr << "Failed to get xinput state. Code: " << dwResult << '\n';
				throw std::runtime_error("Failed to get xinput state. Code: " + std::to_string(dwResult));
			}
		}
	}
}

void dae::InputManager::InputManagerImplementation::AddPlayer()
{
	++m_PlayerCount;
}

dae::InputManager::InputManager() : m_ImplementationPtr{ std::make_unique<InputManagerImplementation>(m_InputActions) }
{}

dae::InputManager::~InputManager()
{}

void dae::InputManager::Init()
{
	m_ImplementationPtr->Init();
}

bool dae::InputManager::ProcessInput(float deltaTime)
{
	return m_ImplementationPtr->ProcessInput(deltaTime);
}

void dae::InputManager::AddPlayer()
{
	m_ImplementationPtr->AddPlayer();
}
