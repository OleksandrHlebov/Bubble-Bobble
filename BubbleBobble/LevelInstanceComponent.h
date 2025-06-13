#pragma once
#include "Component.h"
#include "AIType.h"
#include "BoulderRolling.h"

namespace dae
{
	struct GameEvent;
	class LevelInstance final : public Component
	{
	public:
		LevelInstance() = delete;
		LevelInstance(GameObject* owner) : Component(owner)
		{
		}
		~LevelInstance() = default;

		LevelInstance(const LevelInstance&) = delete;
		LevelInstance(LevelInstance&&) noexcept = delete;
		LevelInstance& operator=(const LevelInstance&) = delete;
		LevelInstance& operator=(LevelInstance&&) noexcept = delete;

		const AIType& GetZenType() { return m_ZenType; }
		const AIType& GetMaitaType() { return m_MaitaType; }

	private:
		AIType m_ZenType{ 50
						, std::make_pair("Textures/Zen_walking.png", 2)
						, std::make_pair("Textures/Zen_trapped.png", 2)
						, std::make_pair("Textures/Zen_dead.png", 4) 
						, std::make_pair("Textures/watermelon.png", 100)
						, std::make_unique<NullAbility>() };
		AIType m_MaitaType{ 50
						, std::make_pair("Textures/Maita_walking.png", 2)
						, std::make_pair("Textures/Maita_trapped.png", 2)
						, std::make_pair("Textures/Maita_dead.png", 4)
						, std::make_pair("Textures/fries.png", 200)
						, std::make_unique<BoulderRolling>() };
		
	};
}