#include <cmath>
#include "Orbit.h"
#include "GameObject.h"

dae::Orbit::Orbit(GameObject* owner) :
	Component(owner)
{

}

void dae::Orbit::Update(float deltaTime)
{
	m_Angle += m_Speed * deltaTime;
	GetOwner()->SetLocalPosition({ m_Position.x + cosf(m_Angle) * m_Radius, m_Position.y - sinf(m_Angle) * m_Radius, m_Position.z });
}

