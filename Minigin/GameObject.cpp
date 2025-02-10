#include <string>
#include "GameObject.h"
#include <algorithm>
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(float deltaTime)
{
	for (auto& comp : m_Components) comp->Update(deltaTime);
}

void dae::GameObject::FixedUpdate(float deltaTime)
{
	for (auto& comp : m_Components) comp->FixedUpdate(deltaTime);
}

void dae::GameObject::Render() const
{
	const auto& pos = m_TransformSPtr->GetPosition();
	for (auto& comp : m_Components) comp->Render(pos.x, pos.y);
}

void dae::GameObject::RemovePendingDelete()
{
	std::erase_if(m_Components, [](const auto& component) { return component->PendingDelete(); });
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_TransformSPtr->SetPosition(x, y, 0.0f);
}

bool dae::GameObject::AddComponent(std::shared_ptr<Component> compUPtr)
{
	auto resultPair = m_Components.insert(compUPtr);
	return resultPair.second;
}
