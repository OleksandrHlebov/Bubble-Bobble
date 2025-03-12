#include "InputAction.h"



void dae::InputAction::ExecutePressed(float deltaTime, float value /*= 1.f*/)
{
	if (m_PressedPtr)	 
	{
		m_DeltaTime = deltaTime;
		m_Value = value;
		m_PressedPtr->Execute();
	}
}

void dae::InputAction::ExecuteHeld(float deltaTime, float value /*= 1.f*/)
{
	if (m_HeldPtr)	 
	{
		m_DeltaTime = deltaTime;
		m_Value = value;
		m_HeldPtr->Execute();
	}
}

void dae::InputAction::ExecuteReleased(float deltaTime, float value /*= 1.f*/)
{
	if (m_ReleasedPtr) 
	{
		m_DeltaTime = deltaTime;
		m_Value = value;
		m_ReleasedPtr->Execute();
	}
}
