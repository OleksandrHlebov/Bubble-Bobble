#pragma once
#include <glm.hpp>
#include "Component.h"

namespace dae
{
	class Transform final : public Component
	{
	public:
		~Transform() = default;

		const glm::vec3& GetPosition() const { return m_position; }
		void SetPosition(float x, float y, float z);

		void Update(float deltaTime) override;

		void FixedUpdate(float deltaTime) override;

		void Render(float x, float y) const override;

	private:
		glm::vec3 m_position;
	};
}
