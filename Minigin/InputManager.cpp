#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Xinput.h>
#include <iostream>
#include "InputManager.h"
#include "ImguiRenderer.h"
#include <numeric>
#include <iostream>

bool dae::InputManager::ProcessInput(float deltaTime)
{
	m_BlockInputActionRemoval = true;
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) 
		{
			for (InputAction& inputAction : m_InputActions)
			{
				if (e.key.keysym.scancode == inputAction.GetKeybind().KeyboardBinding)
				{
					inputAction.Execute(BindTrigger::Pressed, deltaTime);
				}
			}
		}
		if (e.type == SDL_KEYUP)
		{
			for (InputAction& inputAction : m_InputActions)
			{
				if (e.key.keysym.scancode == inputAction.GetKeybind().KeyboardBinding)
				{
					inputAction.Execute(BindTrigger::Released, deltaTime);
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
		if (state[inputAction.GetKeybind().KeyboardBinding])
		{
			inputAction.Execute(BindTrigger::Held, deltaTime);
		}
	}

	for (uint32_t index{}; index < GetGamepadCount(); ++index)
	{
		Gamepad* gamepad = &m_Gamepads[index];
		if (!gamepad->IsConnected())
			continue;
		XINPUT_STATE* currentState  = (XINPUT_STATE*)gamepad->GetCurrentState();
		XINPUT_STATE* previousState = (XINPUT_STATE*)gamepad->GetPreviousState();

		CopyMemory(previousState, currentState, sizeof(XINPUT_STATE));
		ZeroMemory(currentState, sizeof(XINPUT_STATE));
		DWORD dwResult = XInputGetState(index, currentState);

		if (dwResult != ERROR_SUCCESS)
		{
			if (dwResult != ERROR_DEVICE_NOT_CONNECTED)
			{
				std::cerr << "Failed to get xinput state. Code: " << dwResult << '\n';
				return false;
			}
			else continue;
		}

		WORD buttonChanges = currentState->Gamepad.wButtons ^ previousState->Gamepad.wButtons;
		WORD buttonsPressedThisFrame = buttonChanges & currentState->Gamepad.wButtons;
		WORD buttonsReleasedThisFrame = buttonChanges & (~currentState->Gamepad.wButtons);
		WORD buttonsHeldThisFrame = currentState->Gamepad.wButtons;

		for (InputAction& inputAction : m_InputActions)
		{
			if (inputAction.GetDeviceIndex() != gamepad->GetDeviceIndex())
				continue;

			Gamepad::Binding binding = inputAction.GetKeybind().GamepadBinding;
			Gamepad::ValueProvider provider = binding.BoundProvider;
			WORD keyMask = static_cast<WORD>(binding.BoundButtons);

			if (provider == Gamepad::ValueProvider::None)
			{
				if (keyMask & buttonsPressedThisFrame)
					inputAction.Execute(BindTrigger::Pressed, deltaTime);
				if (keyMask & buttonsHeldThisFrame)
					inputAction.Execute(BindTrigger::Held, deltaTime);
				if (keyMask & buttonsReleasedThisFrame)
					inputAction.Execute(BindTrigger::Released, deltaTime);
			}
			else
			{
				if (keyMask && !(keyMask & buttonsHeldThisFrame))
					continue;
				switch (provider)
				{
				case Gamepad::ValueProvider::None:
					break;
				case Gamepad::ValueProvider::LeftTrigger:
				{
					BYTE currentValue = currentState->Gamepad.bLeftTrigger;
					BYTE previousValue = previousState->Gamepad.bLeftTrigger;
					float currentPercent = ToPercentOfMax<BYTE>(currentValue);
					float previousPercent = ToPercentOfMax<BYTE>(previousValue);
					ExecuteValue(inputAction, currentPercent, previousPercent, deltaTime);
					break;
				}
				case Gamepad::ValueProvider::RightTrigger:
				{
					BYTE currentValue = currentState->Gamepad.bRightTrigger;
					BYTE previousValue = previousState->Gamepad.bRightTrigger;
					float currentPercent = ToPercentOfMax<BYTE>(currentValue);
					float previousPercent = ToPercentOfMax<BYTE>(previousValue);
					ExecuteValue(inputAction, currentPercent, previousPercent, deltaTime);
					break;
				}
				case Gamepad::ValueProvider::LeftThumbX:
				{
					SHORT currentValue = currentState->Gamepad.sThumbLX;
					SHORT previousValue = previousState->Gamepad.sThumbLX;
					float currentPercent = ToPercentOfMax<SHORT>(currentValue);
					float previousPercent = ToPercentOfMax<SHORT>(previousValue);
					if (abs(currentPercent) < gamepad->GetDeadzone())
						currentPercent = .0f;
					if (abs(previousPercent) < gamepad->GetDeadzone())
						previousPercent = .0f;
					ExecuteValue(inputAction, currentPercent, previousPercent, deltaTime);
					break;
				}
				case Gamepad::ValueProvider::LeftThumbY:
				{
					SHORT currentValue = currentState->Gamepad.sThumbLY;
					SHORT previousValue = previousState->Gamepad.sThumbLY;
					float currentPercent = ToPercentOfMax<SHORT>(currentValue);
					float previousPercent = ToPercentOfMax<SHORT>(previousValue);
					if (abs(currentPercent) < gamepad->GetDeadzone())
						currentPercent = .0f;
					if (abs(previousPercent) < gamepad->GetDeadzone())
						previousPercent = .0f;
					ExecuteValue(inputAction, currentPercent, previousPercent, deltaTime);
					break;
				}
				case Gamepad::ValueProvider::RightThumbX:
				{
					SHORT currentValue = currentState->Gamepad.sThumbRX;
					SHORT previousValue = previousState->Gamepad.sThumbRX;
					float currentPercent = ToPercentOfMax<SHORT>(currentValue);
					float previousPercent = ToPercentOfMax<SHORT>(previousValue);
					if (abs(currentPercent) < gamepad->GetDeadzone())
						currentPercent = .0f;
					if (abs(previousPercent) < gamepad->GetDeadzone())
						previousPercent = .0f;
					ExecuteValue(inputAction, currentPercent, previousPercent, deltaTime);
					break;
				}
				case Gamepad::ValueProvider::RightThumbY:
				{
					SHORT currentValue = currentState->Gamepad.sThumbRY;
					SHORT previousValue = previousState->Gamepad.sThumbRY;
					float currentPercent = ToPercentOfMax<SHORT>(currentValue);
					float previousPercent = ToPercentOfMax<SHORT>(previousValue);
					if (abs(currentPercent) < gamepad->GetDeadzone())
						currentPercent = .0f;
					if (abs(previousPercent) < gamepad->GetDeadzone())
						previousPercent = .0f;
					ExecuteValue(inputAction, currentPercent, previousPercent, deltaTime);
					break;
				}
				default:
					break;
				}
			}
		}
	}

	m_BlockInputActionRemoval = false;
	while (!m_InputActionsToRemove.empty())
	{
		InputAction* ia = m_InputActionsToRemove.top();
		std::erase(m_InputActions, ia);
		m_InputActionsToRemove.pop();
	}
	return true;
}

dae::InputManager::InputManager()
{
	for (uint32_t index{}; index < GetGamepadCount(); ++index)
	{
		Gamepad* gamepad = &m_Gamepads[index];
		CopyMemory(gamepad->GetPreviousState(), gamepad->GetCurrentState(), sizeof(XINPUT_STATE));
		ZeroMemory(gamepad->GetCurrentState(), sizeof(XINPUT_STATE));
		DWORD dwResult = XInputGetState(index, (XINPUT_STATE*)gamepad->GetCurrentState());
		if (dwResult != ERROR_SUCCESS)
		{
			if (dwResult == ERROR_DEVICE_NOT_CONNECTED)
			{
				std::cerr << "Controller " << index << " not connected\n";
				continue;
			}
			else
			{
				std::cerr << "Failed to get xinput state. Code: " << dwResult << '\n';
				throw std::runtime_error("Failed to get xinput state. Code: " + std::to_string(dwResult));
			}
		}
		gamepad->SetConnectionResult(true);
	}
}

dae::InputManager::~InputManager()
{}

size_t dae::InputManager::GetGamepadCount()
{
	return std::count_if(m_Gamepads.begin(), m_Gamepads.end(), [](const Gamepad& gamepad){ return gamepad.IsConnected(); });
}

dae::Gamepad* dae::InputManager::GetGamepadByPlayerIndex(uint32_t index)
{
	auto it = std::find_if(m_Gamepads.begin(), m_Gamepads.end(), [index](const Gamepad& gamepad)
		{
			return gamepad.GetPlayerIndex() == index;
		});
	
	if (it == m_Gamepads.end())
		return nullptr;

	return &(*it);
}

dae::Gamepad* dae::InputManager::GetFirstAvailableGamepad()
{
	for (Gamepad& gamepad : m_Gamepads)
	{
		if (gamepad.GetPlayerIndex() > m_Gamepads.size())
			return &gamepad;
	}
	return nullptr;
}

void dae::InputManager::RemoveInputAction(InputAction* inputAction)
{
	if (m_BlockInputActionRemoval)
	{
		m_InputActionsToRemove.push(inputAction);
		return;
	}
	std::erase(m_InputActions, inputAction);
}
