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

			void Execute(GameObject* object, float value, float deltaTime) override
			{
				(void)value;
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

			void Execute(GameObject* object, float value, float deltaTime) override
			{
				(void)value;
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

			void Execute(GameObject* object, float value, float deltaTime) override
			{
				(void)value;
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

			void Execute(GameObject* object, float value, float deltaTime) override
			{
				(void)value;
				(void)deltaTime;
				MovementComponent* movement = object->GetComponent<MovementComponent>();
				movement->AddMovementInput(glm::vec3(-1.f, .0f, .0f));
			}

		protected:

		private:

		};

		class UpDown final : public Command
		{
		public:
			UpDown() = default;
			~UpDown() = default;

			UpDown(const UpDown&) = delete;
			UpDown(UpDown&&) noexcept = delete;
			UpDown& operator=(const UpDown&) = delete;
			UpDown& operator=(UpDown&&) noexcept = delete;

			void Execute(GameObject* object, float value, float deltaTime) override
			{
				(void)deltaTime;
				MovementComponent* movement = object->GetComponent<MovementComponent>();
				movement->AddMovementInput(glm::vec3(.0f, -value, .0f));
			}

		protected:

		private:

		};
		class LeftRight final : public Command
		{
		public:
			LeftRight() = default;
			~LeftRight() = default;

			LeftRight(const LeftRight&) = delete;
			LeftRight(LeftRight&&) noexcept = delete;
			LeftRight& operator=(const LeftRight&) = delete;
			LeftRight& operator=(LeftRight&&) noexcept = delete;

			void Execute(GameObject* object, float value, float deltaTime) override
			{
				(void)deltaTime;
				MovementComponent* movement = object->GetComponent<MovementComponent>();
				movement->AddMovementInput(glm::vec3(value, .0f, .0f));
			}

		protected:

		private:

		};
	}
}