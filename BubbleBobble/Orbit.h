#pragma once
#include "Component.h"
#include "glm.hpp"

namespace dae
{
	class Orbit final : public Component
	{
	public:
		Orbit(GameObject* owner);
		~Orbit() = default;
		
		Orbit(const Orbit&) 				= delete;
		Orbit(Orbit&&) noexcept 			= delete;
		Orbit& operator=(const Orbit&) 	 	= delete;
		Orbit& operator=(Orbit&&) noexcept 	= delete;

		void SetPosition(const glm::vec3& position) { m_Position = position; }
		void SetSpeed(float val) { m_Speed = val; }

		void Update(float deltaTime) override;

	private:
		glm::vec3 m_Position{};

		float m_Radius{ 30 };
		float m_Speed{ 10 };
		float m_Angle{};
	};
}