#include "MovementComponent.h"
#include "GameObject.h"

void dae::MovementComponent::AddMovementInput(glm::vec3 inputVector)
{
	m_QueriedInput += inputVector;
	if (m_QueriedInput != glm::vec3{ .0f, .0f, .0f })
		m_QueriedInput = glm::normalize(m_QueriedInput);
}

void dae::MovementComponent::Jump()
{
	GameEvent::Dispatch<OnJump>();
	m_ShouldJump = true;
}

void dae::MovementComponent::Update(float deltaTime)
{
	GameObject* owner = GetOwner();
	Transform* transform = owner->GetComponent<Transform>();
	transform->Move(m_QueriedInput * Speed * deltaTime);
	m_QueriedInput = glm::vec3{ .0f, .0f, .0f };

	transform->Move(glm::vec3{ .0f, m_ShouldJump * -JumpHeight, .0f });
	m_ShouldJump = false;
}