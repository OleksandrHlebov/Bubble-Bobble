#include "Component.h"

Component::~Component() {}

void Component::Update(float)
{}

void Component::FixedUpdate(float)
{}

void Component::Render(float, float) const
{}

void Component::Delete()
{
	m_PendingDelete = true;
}

bool Component::PendingDelete() const
{
	return m_PendingDelete;
}
