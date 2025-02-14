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

void dae::GameObject::Render() const
{
	const auto& pos = m_Transform.GetPosition();
	for (auto& comp : m_Components) comp->Render(pos.x, pos.y);
}

void dae::GameObject::ClearPendingDelete()
{
	std::erase_if(m_Components, [](const auto& component) { return component->IsPendingDelete(); });
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}
