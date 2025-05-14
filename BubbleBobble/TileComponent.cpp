#include "TileComponent.h"
#include "GridComponent.h"
#include "GameObject.h"

void dae::TileComponent::Start()
{
	m_OwningGrid = GetOwner()->GetParent()->GetComponent<GridComponent>();
}

bool dae::TileComponent::HasTileAbove()
{
	return m_OwningGrid->GetIsTileActive(m_GridPosition + glm::ivec2(0, -1));
}
