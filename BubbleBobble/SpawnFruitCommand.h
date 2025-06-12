#pragma once
#include "Command.h"
#include <string>

namespace dae
{
	class SpawnFruitCommand final : public GameObjectCommand
	{
	public:
		SpawnFruitCommand() = delete;
		SpawnFruitCommand(GameObject* gameObject, const std::string& texturePath, int value) 
			: GameObjectCommand(gameObject)
			, m_TexturePath{ texturePath }
			, m_Value{ value }
			{}
		~SpawnFruitCommand() = default;

		SpawnFruitCommand(const SpawnFruitCommand&) = delete;
		SpawnFruitCommand(SpawnFruitCommand&&) noexcept = delete;
		SpawnFruitCommand& operator=(const SpawnFruitCommand&) = delete;
		SpawnFruitCommand& operator=(SpawnFruitCommand&&) noexcept = delete;

		void Execute(float deltaTime) override;

	private:
		std::string m_TexturePath;
		int m_Value;
	};
}