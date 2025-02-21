#include <string>
#include "GameObject.h"
#include <algorithm>
#include "ResourceManager.h"
#include "Renderer.h"

void dae::GameObject::Update(float deltaTime)
{
	for (auto& comp : m_Components) comp->Update(deltaTime);
	ClearPendingDelete();
}

void dae::GameObject::FixedUpdate(float deltaTime)
{
	for (auto& comp : m_Components) comp->FixedUpdate(deltaTime);
}

void dae::GameObject::Render()
{
	const auto& pos = GetWorldPosition();
	for (auto& comp : m_Components) comp->Render(pos.x, pos.y);
}

void dae::GameObject::ClearPendingDelete()
{
	std::erase_if(m_Components, [](const auto& component) { return component->IsPendingDelete(); });
}

void dae::GameObject::SetParent(GameObject* parent, bool keepWorldPosition)
{
	if (parent == this || HasAsParent(parent) || IsChildOf(parent))
		return;

	if (parent == nullptr)
		SetLocalPosition(GetWorldPosition());
	else
	{
		if (keepWorldPosition)
			SetLocalPosition(GetWorldPosition() - parent->GetWorldPosition());
		m_Transform.SetPositionDirty();
	}

	if (m_ParentPtr)
		m_ParentPtr->RemoveChild(this);

	m_ParentPtr = parent;

	if (m_ParentPtr)
		parent->m_Children.insert(this);
}

void dae::GameObject::AddChild(GameObject* child)
{
	if (child == nullptr)
		return;

	if (HasAsParent(child))
		return;

	child->SetParent(this);
}

void dae::GameObject::RemoveChild(GameObject* child)
{
	if (m_Children.erase(child))
		child->SetParent(nullptr, true);
}

bool dae::GameObject::HasAsParent(GameObject* object)
{
	if (m_ParentPtr == nullptr)
		return false;

	if (m_ParentPtr == object)
		return true;

	return m_ParentPtr->HasAsParent(object);
}

bool dae::GameObject::IsChildOf(GameObject* object)
{
	return std::find(m_Children.begin(), m_Children.end(), object) != m_Children.end();
}

void dae::GameObject::SetLocalPosition(float x, float y)
{
	m_Transform.SetLocalPosition(x, y, 0.0f);
}

void dae::GameObject::SetLocalPosition(const glm::vec3& pos)
{
	m_Transform.SetLocalPosition(pos);
}
