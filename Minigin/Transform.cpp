#include "Transform.h"
#include "GameObject.h"

dae::Transform::Transform(GameObject* owner) :
	Component(owner)
{

}

void dae::Transform::SetLocalPosition(const float x, const float y, const float z)
{
	SetLocalPosition({ x, y, z });
}

void dae::Transform::SetPositionDirty()
{
	m_IsPositionDirty = true;
}

const glm::vec3& dae::Transform::GetWorldPosition()
{
	UpdateWorldPosition();
	return m_WorldPosition;
}

bool dae::Transform::IsPositionDirty()
{
	return m_IsPositionDirty;
}

void dae::Transform::SetLocalPosition(const glm::vec3& pos)
{
	m_LocalPosition = pos;
	SetPositionDirty();
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

void dae::Transform::UpdateWorldPosition()
{
	if (m_IsPositionDirty) 
	{
		GameObject* parent{ GetOwner()->GetParent() };
		if (parent)
		{
			Transform* parentTransform{ parent->GetComponent<Transform>() };
			m_WorldPosition = parentTransform->GetWorldPosition() + m_LocalPosition;
		}
		else
			m_WorldPosition = m_LocalPosition;
	}
	m_IsPositionDirty = false;
}
