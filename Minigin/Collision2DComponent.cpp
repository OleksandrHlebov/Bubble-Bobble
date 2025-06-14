#include "Collision2DComponent.h"
#include "Transform.h"
#include "GameObject.h"
#include "Render2DComponent.h"
#include "Scene.h"
#include "Renderer.h"

dae::Collision2DComponent::Collision2DComponent(bool isDynamic, GameObject* owner) : Component(owner)
, m_IsDynamic{ isDynamic }
{
	owner->GetScene()->AddCollider(this);
}

void dae::Collision2DComponent::Render() const
{
#ifndef NDEBUG
	if (m_DrawDebug)
	{
		auto [min, max] = GetBounds();

		Renderer::GetInstance().DrawLine(min.x, min.y, min.x, max.y, 255, 0, 0, 255);
		Renderer::GetInstance().DrawLine(min.x, min.y, max.x, min.y, 255, 0, 0, 255);
		Renderer::GetInstance().DrawLine(max.x, max.y, max.x, min.y, 255, 0, 0, 255);
		Renderer::GetInstance().DrawLine(max.x, max.y, min.x, max.y, 255, 0, 0, 255);
	}
#endif
}

void dae::Collision2DComponent::SetSize(float x, float y)
{
	SetSize(glm::vec2(x, y));
}

glm::vec2 dae::Collision2DComponent::GetSize() const
{
	const glm::vec3 scale{ GetOwner()->GetScale() };
	const glm::vec2 scale2d{ scale.x, scale.y };
	return m_OriginalSize * scale2d;
}

void dae::Collision2DComponent::ProcessOverlaps()
{
	if (!m_IsEnabled)
		return;
	for (auto& collider : GetOwner()->GetScene()->GetDynamicCollisions())
		IsOverlapping(collider);
	for (auto& collider : GetOwner()->GetScene()->GetStaticCollisions())
		IsOverlapping(collider);
}

void dae::Collision2DComponent::SetSize(const glm::vec2& size)
{
	m_OriginalSize = size;
}

bool dae::Collision2DComponent::IsOverlapping(Collision2DComponent* other)
{
	auto [ selfMin,  selfMax] = GetBounds();
	auto [otherMin, otherMax] = other->GetBounds();

	if (this == other)
		return false;

	// self is left of other
	if (selfMax.x < otherMin.x)
		return false;
	// other is left of self
	if (otherMax.x < selfMin.x)
		return false;
	// self is above other
	if (selfMax.y < otherMin.y)
		return false;
	// other is above self
	if (otherMax.y < selfMin.y)
		return false;

	static const float COS_45_DEG{ 0.70710678118f };
	const glm::vec2 collisionDirection = glm::sign((selfMin + selfMax) * .5f - (otherMin + otherMax) * .5f);
	const glm::vec2 collisionNormal = collisionDirection * ((abs(collisionDirection.x) == abs(collisionDirection.y)) ? COS_45_DEG : 1.f);
	const glm::vec2 overlap
	{
		std::min(selfMax.x, otherMax.x) - std::max(selfMin.x, otherMin.x),
		std::min(selfMax.y, otherMax.y) - std::max(selfMin.y, otherMin.y)
	};
	GameEvent::Dispatch<OnOverlap>(GetOwner(), this, other->GetOwner(), other, std::move(overlap), std::move(collisionNormal));

	return true;
}

void dae::Collision2DComponent::SetEnabled(bool isEnabled)
{
	if (isEnabled == !m_IsEnabled)
	{
		if (isEnabled)
			GetOwner()->GetScene()->AddCollider(this);
		else
			GetOwner()->GetScene()->RemoveCollider(this);
	}
	m_IsEnabled = isEnabled;
}

void dae::Collision2DComponent::End()
{
	GetOwner()->GetScene()->RemoveCollider(this);
}

std::pair<glm::vec2, glm::vec2> dae::Collision2DComponent::GetBounds() const
{
	const Transform* transform = GetOwner()->GetComponent<Transform>();
	const glm::vec3& position = transform->GetWorldPosition();
	const glm::vec3& scale = transform->GetScale();
	const glm::vec2 pos2D{ position.x, position.y };
	return { pos2D, glm::vec2{ pos2D + m_OriginalSize * glm::vec2{ scale.x, scale.y } } };
}

glm::vec2 dae::Collision2DComponent::GetCenter() const
{
	auto [min, max] = GetBounds();
	return (min + max) / 2.f;
}
