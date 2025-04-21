#include <string>
#include "GameObject.h"
#include <algorithm>
#include "ResourceManager.h"
#include "Renderer.h"
#include "Controller.h"

dae::GameObject::GameObject()
{}

dae::GameObject::~GameObject()
{}

void dae::GameObject::Start()
{
	for (auto& comp : m_Components) comp->Start();
}

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

void dae::GameObject::RenderUI()
{
	for (auto& comp : m_Components) comp->RenderUI();
}

void dae::GameObject::End()
{
	for (auto& comp : m_Components) comp->End();
}

void dae::GameObject::Delete()
{
	m_PendingDelete = true;
	End();

	for (GameObject*& child : m_Children)
	{
		child->Delete();
	}
}

void dae::GameObject::ClearPendingDelete()
{
	std::erase_if(m_Components, [](const auto& component) { return component->IsPendingDelete(); });
}

void dae::GameObject::RemoveChild(GameObject* child)
{
	m_Children.erase(std::remove(m_Children.begin(), m_Children.end(), child));
}

void dae::GameObject::InvalidatePositionsOfChildren()
{
	for (auto& child : m_Children)
		child->GetComponent<Transform>()->SetPositionDirty();
}

void dae::GameObject::AttachTo(GameObject* parent, bool keepWorldPosition)
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
		parent->m_Children.emplace_back(this);
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
	SetLocalPosition({ x, y, .0f });
}

const glm::vec3& dae::GameObject::GetWorldPosition()
{
	return m_Transform.GetWorldPosition();
}

void dae::GameObject::SetLocalPosition(const glm::vec3& pos)
{
	m_Transform.SetLocalPosition(pos);
}
