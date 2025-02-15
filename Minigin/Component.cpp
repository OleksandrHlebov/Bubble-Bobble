#include "Component.h"
#include <typeinfo>

using namespace dae;

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

bool Component::IsPendingDelete() const
{
	return m_PendingDelete;
}