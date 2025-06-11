#include "Transform.h"
#include "GameObject.h"
#include <iostream>
#include "Collision2DComponent.h"

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
	InvalidatePositionsOfChildren();
}

void dae::Transform::Move(const glm::vec3& delta, bool sweep)
{
	if (delta != glm::vec3{})
	{
		SetLocalPosition(GetLocalPosition() + delta);
		if (sweep)
			if (Collision2DComponent* collision = GetOwner()->GetComponent<Collision2DComponent>())
				collision->ProcessOverlaps();
			else
				std::cerr << "transform sweep requested on object with no collider\n";
	}
}

const glm::vec3& dae::Transform::GetWorldPosition() const
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

void dae::Transform::Render() const
{
}

void dae::Transform::UpdateWorldPosition() const
{
	if (m_IsPositionDirty) 
	{
		const GameObject* parent{ GetOwner()->GetParent() };
		if (parent)
		{
			const Transform* parentTransform{ parent->GetComponent<Transform>() };
			m_WorldPosition = parentTransform->GetWorldPosition() + m_LocalPosition;
		}
		else
			m_WorldPosition = m_LocalPosition;
	}
	m_IsPositionDirty = false;
}

void dae::Transform::InvalidatePositionsOfChildren()
{
	GetOwner()->InvalidatePositionsOfChildren();
}
