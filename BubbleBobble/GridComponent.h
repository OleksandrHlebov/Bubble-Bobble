#pragma once
#include "Component.h"
#include <vector>
#include <string>
#include <memory>
#include <glm.hpp>

namespace dae { class Texture2D; }

namespace dae
{
	class GameObject;
	class GridComponent final : public Component
	{
	public:
		GridComponent() = delete;
		GridComponent(int rows, int cols, glm::ivec2 gridSize, GameObject* owner)
			: Component(owner)
			, m_Rows{ rows }
			, m_Cols{ cols }
			, m_TileSize{ gridSize.x / cols, gridSize.y / rows }
		{
			m_Tiles.resize(rows * cols, false);
		}
		~GridComponent() = default;
		
		GridComponent(const GridComponent&) 				= delete;
		GridComponent(GridComponent&&) noexcept 			= delete;
		GridComponent& operator=(const GridComponent&) 	 	= delete;
		GridComponent& operator=(GridComponent&&) noexcept 	= delete;

		void SetTileTexture(std::shared_ptr<Texture2D> texture);

		void EnableTile(int index);
		void EnableRow(int rowIndex);
		void EnableColumn(int colIndex);
		void DisableTile(int index);
		void DisableRow(int rowIndex);
		void DisableColumn(int colIndex);

		bool GetIsTileActive(const glm::ivec2& gridPos);

		int64_t GetTileCount() { return std::ssize(m_Tiles); }

		void Start() override;

		void Render() const override;

	private:
		std::shared_ptr<Texture2D> m_Texture;
		std::vector<bool> m_Tiles;
		glm::ivec2 m_TileSize;
		const int m_BorderThickness{ 2 };
		int m_Rows;
		int m_Cols;

	};
}