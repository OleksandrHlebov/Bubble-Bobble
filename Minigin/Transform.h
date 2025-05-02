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

		const glm::vec3& GetScale() { return m_Scale; }
		void SetScale(const glm::vec3& scale) { m_Scale = scale; }
		void SetScale(float x, float y, float z) { SetScale(glm::vec3{ x, y, z }); }

		const glm::vec3& GetLocalPosition() const { return m_LocalPosition; }
		void SetLocalPosition(float x, float y, float z);
		void SetLocalPosition(const glm::vec3& pos);
		void SetPositionDirty();

		void Move(const glm::vec3& delta);

		const glm::vec3& GetWorldPosition();
		bool IsPositionDirty();

		void Update(float deltaTime) override;

		void FixedUpdate(float deltaTime) override;

		void Render() const override;

	private:
		void UpdateWorldPosition();
		void InvalidatePositionsOfChildren();

		glm::vec3 m_LocalPosition;
		glm::vec3 m_Scale{ 1.f, 1.f, 1.f };

		glm::vec3 m_WorldPosition;

		bool m_IsPositionDirty{ true };
	};
}
