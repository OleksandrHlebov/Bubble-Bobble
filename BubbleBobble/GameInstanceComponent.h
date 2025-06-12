#pragma once
#include "Component.h"
#include "AIType.h"

namespace dae
{
	struct GameEvent;
	class GameInstance final : public Component
	{
	public:
		GameInstance() = delete;
		GameInstance(GameObject* owner) : Component(owner)
		{
		}
		~GameInstance() = default;

		GameInstance(const GameInstance&) = delete;
		GameInstance(GameInstance&&) noexcept = delete;
		GameInstance& operator=(const GameInstance&) = delete;
		GameInstance& operator=(GameInstance&&) noexcept = delete;

		const AIType& GetZenType() { return m_ZenType; }

	private:
		AIType m_ZenType{ 50
						, std::make_pair("Textures/Zen_walking.png", 2)
						, std::make_pair("Textures/Zen_trapped.png", 2)
						, std::make_pair("Textures/Zen_dead.png", 4) };
		
	};
}