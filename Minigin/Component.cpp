#include "Component.h"
#include <typeinfo>

using namespace dae;

Component::~Component() {}

void Component::Update(float)
{}

void Component::FixedUpdate(float)
{}

void Component::LateUpdate(float)
{}

void dae::Component::Render() const
{}

void Component::Delete()
{
	m_PendingDelete = true;
	End();
}

bool Component::IsPendingDelete() const
{
	return m_PendingDelete;
}

Component::Component(GameObject* owner) :
	m_OwnerPtr{ owner }
{}

void Component::RenderUI()
{}

void Component::Start()
{}

void Component::End()
{}

dae::GameObject* dae::Component::GetOwner()
{
	return m_OwnerPtr;
}

const dae::GameObject* Component::GetOwner() const
{
	return m_OwnerPtr;
}
