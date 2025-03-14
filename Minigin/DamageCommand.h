#pragma once
#include "Command.h"

namespace dae
{
	class DamageCommand final : public GameObjectCommand
	{
	public:
		DamageCommand() = delete;
		DamageCommand(GameObject* gameObject, int damage) : GameObjectCommand(gameObject), m_Damage{ damage } {}
		~DamageCommand() = default;
		
		DamageCommand(const DamageCommand&) 					= delete;
		DamageCommand(DamageCommand&&) noexcept 				= delete;
		DamageCommand& operator=(const DamageCommand&) 	 	= delete;
		DamageCommand& operator=(DamageCommand&&) noexcept 	= delete;

		void Execute() override;

	private:
		int m_Damage;
	};
}