#include "Component.h"

Component::~Component() {}

void Component::Delete()
{
	m_PendingDelete = true;
}

bool Component::PendingDelete() const
{
	return m_PendingDelete;
}
