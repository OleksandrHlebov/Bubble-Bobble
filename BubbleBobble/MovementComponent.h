#pragma once
#include "Component.h"
#include "Transform.h"
#include "GameEvent.h"
#include "EventDispatcher.h"
#include "Collision2DComponent.h"

namespace dae
{
	class MovementComponent : public Component
	{
	public:
		struct OnJump final : public GameEvent
		{
			OnJump(GameObject* gameObject) : GameEvent("OnJump"), Object{ gameObject }
			{
			}

			GameObject* const Object;
		};

		MovementComponent() = delete;
		MovementComponent(GameObject* owner) : Component(owner) {}
		~MovementComponent() = default;
		
		MovementComponent(const MovementComponent&) 				= delete;
		MovementComponent(MovementComponent&&) noexcept 			= delete;
		MovementComponent& operator=(const MovementComponent&) 	 	= delete;
		MovementComponent& operator=(MovementComponent&&) noexcept 	= delete;

		void Start() override;

		void AddMovementInput(const glm::vec3& inputVector);

		void Jump();

		void Update(float deltaTime) override;

		void LateUpdate(float deltaTime) override;

		void HandleOverlapping(GameEvent* event);

		bool IsGrounded() { return m_IsGrounded; }

		void End() override;

		void SetEnabled(bool isEnabled);
		void Launch(const glm::vec3& direction, float strength);
		void Launch(const glm::vec3& impulse);

		const glm::vec3& GetVelocity() { return m_Velocity; }
		const glm::vec3& GetForward()  { return m_Forward; }

		float Speed{ 50.f };
		float JumpHeight{ 200.f };
		float InAirSlowdownPercent{ .3f };

	private:
		float ResolveVerticalCollision(Collision2DComponent::OnOverlap* overlapEvent, bool selfIsFirst);

		glm::vec3 m_QueriedInput{};
		glm::vec3 m_Velocity{};
		glm::vec3 m_Forward{ 1.f, .0f, .0f };

		EventHandler m_OverlapHandler{ std::bind(&MovementComponent::HandleOverlapping, this, std::placeholders::_1) };

		inline static const float DOWN_RAY_LENGTH{ 2.f };
		inline static const float RESOLVE_THRESHOLD{ .35f };
		inline static const float GRAVITY_CLAMP{ 50.f };

		bool m_IsEnabled{ true };
		bool m_IsGrounded{};
	};
}