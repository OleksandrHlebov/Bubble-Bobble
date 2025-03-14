#pragma once
#include "Command.h"

namespace dae
{
	class PickUpCommand final : public GameObjectCommand
	{
	public:
		PickUpCommand() = delete;
		PickUpCommand(GameObject* gameObject) : GameObjectCommand(gameObject)
		{
		}
		~PickUpCommand() = default;
		
		PickUpCommand(const PickUpCommand&) 				= delete;
		PickUpCommand(PickUpCommand&&) noexcept 			= delete;
		PickUpCommand& operator=(const PickUpCommand&) 	 	= delete;
		PickUpCommand& operator=(PickUpCommand&&) noexcept 	= delete;

		void Execute() override;

	private:

	};
}