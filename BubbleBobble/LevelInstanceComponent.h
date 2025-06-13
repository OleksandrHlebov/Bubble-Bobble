#pragma once
#include "Component.h"
#include "AIType.h"
#include "BoulderRolling.h"
#include "GameEvent.h"
#include <unordered_map>

namespace dae
{
	class LevelInstance final : public Component
	{
	public:
		using Anim = std::pair<std::string, int>;
		using Treat = Anim;
		LevelInstance() = delete;
		LevelInstance(GameObject* owner) : Component(owner)
		{
			m_DefinedAbilities["Null"] = std::make_unique<NullAbility>();
			m_DefinedAbilities["BoulderRolling"] = std::make_unique<BoulderRolling>();
		}
		~LevelInstance() = default;

		LevelInstance(const LevelInstance&) = delete;
		LevelInstance(LevelInstance&&) noexcept = delete;
		LevelInstance& operator=(const LevelInstance&) = delete;
		LevelInstance& operator=(LevelInstance&&) noexcept = delete;

		const AIType& AddType(float speed, Anim walking, Anim trapped, Anim dead, Treat treat, const std::string& ability)
		{
			if (!m_DefinedAbilities.contains(ability))
				throw std::runtime_error("unknown ability " + ability);
			return *m_Types.emplace_back(std::make_unique<AIType>(speed, walking, trapped, dead, treat, m_DefinedAbilities[ability].get()));
		}

		void Start() override;

		void End() override;

		void HandleDeath(GameEvent*);

		//const AIType& GetZenType() { return m_ZenType; }
		//const AIType& GetMaitaType() { return m_MaitaType; }

	private:
		std::unordered_map<std::string, std::unique_ptr<Ability>> m_DefinedAbilities;
		std::vector<std::unique_ptr<AIType>> m_Types;

		EventHandler m_DeathHandler{ std::bind(&LevelInstance::HandleDeath, this, std::placeholders::_1) };

		//AIType m_ZenType{ 50
		//				, std::make_pair("Textures/Zen_walking.png", 2)
		//				, std::make_pair("Textures/Zen_trapped.png", 2)
		//				, std::make_pair("Textures/Zen_dead.png", 4) 
		//				, std::make_pair("Textures/watermelon.png", 100)
		//				, std::make_unique<NullAbility>() };
		//AIType m_MaitaType{ 50
		//				, std::make_pair("Textures/Maita_walking.png", 2)
		//				, std::make_pair("Textures/Maita_trapped.png", 2)
		//				, std::make_pair("Textures/Maita_dead.png", 4)
		//				, std::make_pair("Textures/fries.png", 200)
		//				, std::make_unique<BoulderRolling>() };
		
	};
}