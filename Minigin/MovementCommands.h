#pragma once
#include "Command.h"
#include "MovementComponent.h"

namespace dae
{
	namespace Move
	{
		class Up final : public Command
		{
		public:
			Up() = default;
			~Up() = default;

			Up(const Up&) = delete;
			Up(Up&&) noexcept = delete;
			Up& operator=(const Up&) = delete;
			Up& operator=(Up&&) noexcept = delete;

			void Execute(GameObject* object, float deltaTime) override
			{
				(void)deltaTime;
				MovementComponent* movement = object->GetComponent<MovementComponent>();
				movement->AddMovementInput(glm::vec3(.0f, -1.f, .0f));
			}

		protected:

		private:

		};
		class Down final : public Command
		{
		public:
			Down() = default;
			~Down() = default;

			Down(const Down&) = delete;
			Down(Down&&) noexcept = delete;
			Down& operator=(const Down&) = delete;
			Down& operator=(Down&&) noexcept = delete;

			void Execute(GameObject* object, float deltaTime) override
			{
				(void)deltaTime;
				MovementComponent* movement = object->GetComponent<MovementComponent>();
				movement->AddMovementInput(glm::vec3(.0f, 1.f, .0f));
			}

		protected:

		private:

		};
		class Right final : public Command
		{
		public:
			Right() = default;
			~Right() = default;

			Right(const Right&) = delete;
			Right(Right&&) noexcept = delete;
			Right& operator=(const Right&) = delete;
			Right& operator=(Right&&) noexcept = delete;

			void Execute(GameObject* object, float deltaTime) override
			{
				(void)deltaTime;
				MovementComponent* movement = object->GetComponent<MovementComponent>();
				movement->AddMovementInput(glm::vec3(1.f, .0f, .0f));
			}

		protected:

		private:

		};
		class Left final : public Command
		{
		public:
			Left() = default;
			~Left() = default;

			Left(const Left&) = delete;
			Left(Left&&) noexcept = delete;
			Left& operator=(const Left&) = delete;
			Left& operator=(Left&&) noexcept = delete;

			void Execute(GameObject* object, float deltaTime) override
			{
				(void)deltaTime;
				MovementComponent* movement = object->GetComponent<MovementComponent>();
				movement->AddMovementInput(glm::vec3(-1.f, .0f, .0f));
			}

		protected:

		private:

		};
	}
}