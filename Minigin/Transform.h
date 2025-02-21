#pragma once
#include <glm.hpp>
#include "Component.h"

namespace dae
{
	class Transform final : public Component
	{
	public:
		Transform(GameObject* owner);
		~Transform() = default;

		Transform(const Transform&) 				= delete;
		Transform(Transform&&) noexcept 			= delete;
		Transform& operator=(const Transform&) 	 	= delete;
		Transform& operator=(Transform&&) noexcept 	= delete;

		const glm::vec3& GetLocalPosition() const { return m_LocalPosition; }
		void SetLocalPosition(float x, float y, float z);
		void SetLocalPosition(const glm::vec3& pos);
		void SetPositionDirty();

		const glm::vec3& GetWorldPosition();
		bool IsPositionDirty();

		void Update(float deltaTime) override;

		void FixedUpdate(float deltaTime) override;

		void Render(float x, float y) const override;

	private:
		void UpdateWorldPosition();

		glm::vec3 m_LocalPosition;
		glm::vec3 m_WorldPosition;

		bool m_IsPositionDirty{ true };
	};
}
