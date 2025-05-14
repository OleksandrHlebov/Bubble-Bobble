#include "GridComponent.h"
#include <cassert>
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "Render2DComponent.h"
#include "Collision2DComponent.h"
#include "Texture2D.h"
#include "RenderPriorities.h"
#include "TileComponent.h"

namespace dae
{

	void GridComponent::SetTileTexture(std::shared_ptr<Texture2D> texture)
	{
		m_Texture = texture;
	}

	void GridComponent::EnableTile(int index)
	{
		assert(index < GetTileCount());
		m_Tiles[index] = true;
	}

	void GridComponent::EnableRow(int rowIndex)
	{
		assert(rowIndex < m_Rows);
		for (int index{}; index < m_Cols; ++index)
			m_Tiles[rowIndex * m_Cols + index] = true;
	}

	void GridComponent::EnableColumn(int colIndex)
	{
		assert(colIndex < m_Cols);
		for (int index{}; index < m_Rows; ++index)
			m_Tiles[index * m_Cols + colIndex] = true;
	}

	void GridComponent::Render() const
	{
	#ifndef NDEBUG
		//for (int x{ 1 }; x <= m_Cols; ++x)
		//	Renderer::GetInstance().DrawLine(x * m_TileSize.x, 0, x * m_TileSize.x, m_Rows * m_TileSize.y, 255, 0, 0, 255);
		//for (int y{ 1 }; y <= m_Rows; ++y)
		//	Renderer::GetInstance().DrawLine(0, y * m_TileSize.y, m_Cols * m_TileSize.x, y * m_TileSize.y, 255, 0, 0, 255);
	#endif
	}

	void GridComponent::DisableTile(int index)
	{
		assert(index < GetTileCount());
		m_Tiles[index] = false;
	}

	void GridComponent::DisableRow(int rowIndex)
	{
		assert(rowIndex < m_Rows);
		for (int index{}; index < m_Cols; ++index)
			m_Tiles[rowIndex * m_Cols + index] = false;
	}

	void GridComponent::DisableColumn(int colIndex)
	{
		assert(colIndex < m_Cols);
		for (int index{}; index < m_Rows; ++index)
			m_Tiles[index * m_Cols + colIndex] = false;
	}

	bool GridComponent::GetIsTileActive(const glm::ivec2& gridPos)
	{
		const int transformed1DIndex{ gridPos.x + gridPos.y * m_Cols };
		assert(transformed1DIndex < GetTileCount());
		return m_Tiles[transformed1DIndex];
	}

	void GridComponent::Start()
	{
		if (!m_Texture)
			m_Texture = ResourceManager::GetInstance().LoadTexture("Textures/Level/Tile_1.png");
		for (int index{}; index < m_Tiles.size(); ++index)
			if (m_Tiles[index])
			{
				GameObject* tile = GetOwner()->GetScene()->CreateGameObject();
				tile->AttachTo(GetOwner());
				tile->SetLocalPosition(static_cast<float>(index % m_Cols * m_TileSize.x), static_cast<float>(index / m_Cols * m_TileSize.y));
				tile->AddComponent<TileComponent>(glm::ivec2{ index % m_Cols, index / m_Cols });
				tile->AddComponent<Render2DComponent>()->SetTexture(m_Texture);
				tile->AddComponent<Collision2DComponent>(false)->SetSize(m_Texture->GetSize());
			}
	}

}