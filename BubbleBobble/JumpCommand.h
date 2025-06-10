#pragma once
#include "AudioLocator.h"
#include "Sound.h"

namespace dae
{
	class JumpCommand final : public GameObjectCommand
	{
	public:
		JumpCommand() = delete;
		JumpCommand(GameObject* gameObject) : GameObjectCommand(gameObject)
		{
		}
		~JumpCommand() = default;
		
		JumpCommand(const JumpCommand&) 				= delete;
		JumpCommand(JumpCommand&&) noexcept 			= delete;
		JumpCommand& operator=(const JumpCommand&) 	 	= delete;
		JumpCommand& operator=(JumpCommand&&) noexcept 	= delete;

		void Execute(float) override
		{
			MovementComponent* movement = GetGameObject()->GetComponent<MovementComponent>();
			movement->Jump();
		}

	private:

	};
}