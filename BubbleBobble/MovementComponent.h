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

		void Start() override;

		void AddMovementInput(glm::vec3 inputVector);

		void Jump();

		void Update(float deltaTime) override;

		void LateUpdate(float deltaTime) override;

		void HandleOverlapping(GameEvent* event);

		const glm::vec3& GetVelocity() { return m_Velocity; }

		float Speed{ 50.f };
		float JumpHeight{ 200.f };


	private:
		glm::vec3 m_QueriedInput{};
		glm::vec3 m_Velocity{};

		inline static const float DownRayLength{ 1.f };
		inline static const float ResolveThreshold{ .35f };

		bool m_IsGrounded{};
	};
}