#pragma once
#include "Command.h"
#include "MovementComponent.h"
#include "glm.hpp"
#include "InputAction.h"

namespace dae
{
	class MoveCommand final : public GameObjectCommand
	{
	public:
		MoveCommand() = delete;
		MoveCommand(GameObject* gameObject, glm::vec3 direction) : GameObjectCommand(gameObject), m_Direction{ direction }
		{
		}
		~MoveCommand() = default;

		MoveCommand(const MoveCommand&) = delete;
		MoveCommand(MoveCommand&&) noexcept = delete;
		MoveCommand& operator=(const MoveCommand&) = delete;
		MoveCommand& operator=(MoveCommand&&) noexcept = delete;

		void Execute(float) override
		{
			MovementComponent* movement = GetGameObject()->GetComponent<MovementComponent>();
			if (movement)
				movement->AddMovementInput(m_Direction);
		}

		void SetDirection(const glm::vec3& direction) { m_Direction = direction; }

	protected:

	private:
		glm::vec3 m_Direction;
	};
}