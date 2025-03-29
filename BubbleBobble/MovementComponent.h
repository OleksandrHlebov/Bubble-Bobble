#pragma once
#include "Component.h"
#include "Transform.h"

namespace dae
{
	class GameObject;
	class MovementComponent : public Component
	{
	public:
		MovementComponent() = delete;
		MovementComponent(GameObject* owner) : Component(owner) {}
		~MovementComponent() = default;
		
		MovementComponent(const MovementComponent&) 				= delete;
		MovementComponent(MovementComponent&&) noexcept 			= delete;
		MovementComponent& operator=(const MovementComponent&) 	 	= delete;
		MovementComponent& operator=(MovementComponent&&) noexcept 	= delete;

		void AddMovementInput(glm::vec3 inputVector);

		void Update(float deltaTime) override;

		float Speed{ 10.f };

	private:
		glm::vec3 m_QueriedInput{};

	};
}