#pragma once
#include "Command.h"
#include "GameEvent.h"

namespace dae
{
	struct OnBurp final : public GameEvent
	{
		OnBurp() = delete;
		explicit OnBurp(GameObject* gameObject)
			: GameEvent("OnBurp"), Object{ gameObject }
		{}

		const GameObject* Object;
	};
	class BurpCommand final : public GameObjectCommand
	{
	public:
		BurpCommand() = delete;
		BurpCommand(GameObject* gameObject) : GameObjectCommand(gameObject) {}
		~BurpCommand() = default;
		
		BurpCommand(const BurpCommand&) 				= delete;
		BurpCommand(BurpCommand&&) noexcept 			= delete;
		BurpCommand& operator=(const BurpCommand&) 	 	= delete;
		BurpCommand& operator=(BurpCommand&&) noexcept 	= delete;

		void Execute(float deltaTime) override;

	};
}