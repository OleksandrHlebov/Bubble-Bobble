#include <string>
#include "GameObject.h"
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

void dae::GameObject::SetPosition(float x, float y)
{
	m_TransformSPtr->SetPosition(x, y, 0.0f);
}

void dae::GameObject::AddComponent(std::shared_ptr<Component> compUPtr)
{
	m_Components.insert(compUPtr);
}
