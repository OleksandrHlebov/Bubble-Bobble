#include "Transform.h"

dae::Transform::Transform(GameObject* owner) :
	Component(owner)
{

}

void dae::Transform::SetPosition(const float x, const float y, const float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}

void dae::Transform::Update(float)
{
}

void dae::Transform::FixedUpdate(float)
{
}

void dae::Transform::Render(float, float) const
{
}
