#include "MovementComponent.h"
#include "GameObject.h"
#include <algorithm>

void dae::MovementComponent::AddMovementInput(glm::vec3 inputVector)
{
	m_QueriedInput += inputVector;
}

void dae::MovementComponent::Jump()
{
	m_ShouldJump = m_IsGrounded;
}

void dae::MovementComponent::Update(float deltaTime)
{
	const float GRAVITY{ JumpHeight * 2.1f };

	GameObject* owner = GetOwner();
	Transform* transform = owner->GetComponent<Transform>();
	// dirty debug way for grounding
	m_IsGrounded = transform->GetWorldPosition().y >= 200.f; 

	float horizontalMovement{ m_QueriedInput.x * Speed };

	m_Velocity.x = horizontalMovement;
	if (!m_IsGrounded)
		m_Velocity.y = std::min(m_Velocity.y + GRAVITY * deltaTime, GRAVITY);
	m_Velocity.y *= !m_IsGrounded;
	if (m_ShouldJump)
	{
		m_Velocity.y = -JumpHeight;
		GameEvent::Dispatch<OnJump>();
		m_ShouldJump = false;
	}
	transform->Move(m_Velocity * deltaTime);
}

void dae::MovementComponent::LateUpdate(float)
{
	m_QueriedInput = glm::vec3{};
}
