#pragma once
#include "Component.h"
#include <glm.hpp>

namespace dae
{
	class GridComponent;
	class TileComponent final : public Component
	{
	public:
		TileComponent() = delete;
		TileComponent(const glm::ivec2& gridPos, GameObject* owner) 
			: Component(owner)
			, m_GridPosition{ gridPos }
			{}
		~TileComponent() = default;
		
		TileComponent(const TileComponent&) 				= delete;
		TileComponent(TileComponent&&) noexcept 			= delete;
		TileComponent& operator=(const TileComponent&) 	 	= delete;
		TileComponent& operator=(TileComponent&&) noexcept  = delete;

		void Start() override;

		const glm::ivec2& GetGridPosition() { return m_GridPosition; }
		bool HasTileAbove();

		GridComponent* GetGrid() { return m_OwningGrid; }

	private:
		GridComponent* m_OwningGrid;

		glm::ivec2 m_GridPosition;
	};
}