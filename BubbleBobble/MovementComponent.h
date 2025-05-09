#pragma once
#include "Component.h"
#include "Transform.h"
#include "GameEvent.h"

namespace dae
{
	class GameObject;
	class MovementComponent : public Component
	{
	public:
		struct OnJump final : public GameEvent
		{
			OnJump() : GameEvent("OnJump")
			{
			}
		};

		MovementComponent() = delete;
		MovementComponent(GameObject* owner) : Component(owner) {}
		~MovementComponent() = default;
		
		MovementComponent(const MovementComponent&) 				= delete;
		MovementComponent(MovementComponent&&) noexcept 			= delete;
		MovementComponent& operator=(const MovementComponent&) 	 	= delete;
		MovementComponent& operator=(MovementComponent&&) noexcept 	= delete;

		void AddMovementInput(glm::vec3 inputVector);

		void Jump();

		void Update(float deltaTime) override;

		void LateUpdate(float deltaTime) override;

		const glm::vec3& GetVelocity() { return m_Velocity; }

		float Speed{ 50.f };
		float JumpHeight{ 200.f };

	private:
		glm::vec3 m_QueriedInput{};
		glm::vec3 m_Velocity{};
		
		bool m_ShouldJump{};
		bool m_IsGrounded{};
	};
}