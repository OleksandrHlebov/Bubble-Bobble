#include "Gamepad.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Xinput.h>

uint32_t dae::operator|(Gamepad::Button left, Gamepad::Button right)
{
	return static_cast<uint32_t>(static_cast<uint32_t>(left) | static_cast<uint32_t>(right));
}

class dae::Gamepad::GamepadImplementation : public dae::Gamepad
{
public:
	GamepadImplementation() : Gamepad(true) {}
	~GamepadImplementation() = default;
	
	GamepadImplementation(const GamepadImplementation&) 				= delete;
	GamepadImplementation(GamepadImplementation&&) noexcept 			= delete;
	GamepadImplementation& operator=(const GamepadImplementation&) 	 	= delete;
	GamepadImplementation& operator=(GamepadImplementation&&) noexcept 	= delete;

	static uint32_t GetCount() { return m_Count; }
	uint32_t GetIndex() { return m_Index; }

	XINPUT_STATE* GetCurrentState() { return &m_CurrentState; }
	XINPUT_STATE* GetPreviousState() { return &m_PreviousState; }

#ifdef _DEBUG
	glm::vec2 DEBUG_GetLeftThumbInput()
	{
		return { m_CurrentState.Gamepad.sThumbLX, m_CurrentState.Gamepad.sThumbLY };
	}
#endif

	void SetDeadzone(float deadzone) { m_Deadzone = deadzone; }
	float GetDeadzone() { return m_Deadzone; }

private:
	inline static uint32_t m_Count{};
	uint32_t m_Index;
	XINPUT_STATE m_CurrentState{};
	XINPUT_STATE m_PreviousState{};

	float m_Deadzone{ .05f };
};

dae::Gamepad::Gamepad() : m_ImplementationPtr{ std::make_unique<GamepadImplementation>() }
{
}

dae::Gamepad::Gamepad(bool ignoreImplementationPtr)
{
	(void)ignoreImplementationPtr;
}

dae::Gamepad::~Gamepad()
{

}

uint32_t dae::Gamepad::GetCount()
{
	return GamepadImplementation::GetCount();
}

uint32_t dae::Gamepad::GetIndex()
{
	return m_ImplementationPtr->GetIndex();
}

#ifdef _DEBUG
glm::vec2 dae::Gamepad::DEBUG_GetLeftThumbInput()
{
	return m_ImplementationPtr->DEBUG_GetLeftThumbInput();
}
#endif

void dae::Gamepad::SetDeadzone(float deadzone)
{
	m_ImplementationPtr->SetDeadzone(deadzone);
}

float dae::Gamepad::GetDeadzone()
{
	return m_ImplementationPtr->GetDeadzone();
}

void* dae::Gamepad::GetCurrentState()
{
	return m_ImplementationPtr->GetCurrentState();
}

void* dae::Gamepad::GetPreviousState()
{
	return m_ImplementationPtr->GetPreviousState();
}
