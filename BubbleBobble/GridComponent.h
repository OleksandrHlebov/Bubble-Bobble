#pragma once
#include "Component.h"
#include <vector>

namespace dae
{
	class GameObject;
	class Render2DComponent;
	class GridComponent final : public Component
	{
	public:
		GridComponent() = delete;
		GridComponent(GameObject* owner, int rows, int cols, int tileSize) 
			: Component(owner)
			, m_TileSize{ tileSize }
		{
			m_Tiles.resize(rows * cols, false);
		}
		~GridComponent() = default;
		
		GridComponent(const GridComponent&) 				= delete;
		GridComponent(GridComponent&&) noexcept 			= delete;
		GridComponent& operator=(const GridComponent&) 	 	= delete;
		GridComponent& operator=(GridComponent&&) noexcept 	= delete;

		void Render() const override;

	private:
		Render2DComponent* m_RenderComponentPtr;
		std::vector<bool> m_Tiles;
		int m_TileSize;

	};
}