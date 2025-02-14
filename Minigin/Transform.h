#pragma once
#include <glm.hpp>
#include "Component.h"

namespace dae
{
	class Transform final : public Component
	{
	public:
		Transform() = default;
		~Transform() = default;

		Transform(const Transform&) 				= delete;
		Transform(Transform&&) noexcept 			= delete;
		Transform& operator=(const Transform&) 	 	= delete;
		Transform& operator=(Transform&&) noexcept 	= delete;

		const glm::vec3& GetPosition() const { return m_position; }
		void SetPosition(float x, float y, float z);

		void Update(float deltaTime) override;

		void FixedUpdate(float deltaTime) override;

		void Render(float x, float y) const override;

	private:
		glm::vec3 m_position;
	};
}
