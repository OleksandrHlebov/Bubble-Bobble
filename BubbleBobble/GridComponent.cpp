#include "GridComponent.h"
#include <cassert>
#include "Renderer.h"

namespace dae
{

	void GridComponent::Render() const
	{

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

}