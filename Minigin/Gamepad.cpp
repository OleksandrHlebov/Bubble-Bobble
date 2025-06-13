#include "Gamepad.h"
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <Xinput.h>
#include <limits>

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

	uint32_t GetDeviceIndex() const { return m_DeviceIndex; }
	uint32_t GetPlayerIndex() const { return m_PlayerIndex; }
	void AssignToPlayer(uint32_t index) { m_PlayerIndex = index; }

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
	uint32_t m_DeviceIndex{ m_Count++ };
	uint32_t m_PlayerIndex{ std::numeric_limits<uint32_t>::max() };
	XINPUT_STATE m_CurrentState{};
	XINPUT_STATE m_PreviousState{};

	float m_Deadzone{ .05f };
};

dae::Gamepad::Gamepad() : m_ImplementationPtr{ std::make_unique<GamepadImplementation>() }
{
}

dae::Gamepad::Gamepad(bool)
{
}

dae::Gamepad::~Gamepad()
{

}

uint32_t dae::Gamepad::GetDeviceIndex() const
{
	return m_ImplementationPtr->GetDeviceIndex();
}

uint32_t dae::Gamepad::GetPlayerIndex() const
{
	return m_ImplementationPtr->GetPlayerIndex();
}

void dae::Gamepad::AssignToPlayer(uint32_t index)
{
	m_ImplementationPtr->AssignToPlayer(index);
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
