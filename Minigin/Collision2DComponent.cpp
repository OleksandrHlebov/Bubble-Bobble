#include "Collision2DComponent.h"
#include "Transform.h"
#include "GameObject.h"
#include "Render2DComponent.h"
#include "Scene.h"

dae::Collision2DComponent::Collision2DComponent(bool isDynamic, GameObject* owner) : Component(owner)
, m_IsDynamic{ isDynamic }
{
	owner->GetScene()->AddCollider(this);
}

void dae::Collision2DComponent::SetSize(float x, float y)
{
	SetSize(glm::vec2(x, y));
}

void dae::Collision2DComponent::ProcessOverlaps()
{
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

std::pair<glm::vec2, glm::vec2> dae::Collision2DComponent::GetBounds()
{
	Transform* transform = GetOwner()->GetComponent<Transform>();
	const glm::vec3& position = transform->GetWorldPosition();
	const glm::vec3& scale = transform->GetScale();
	const glm::vec2 pos2D{ position.x, position.y };
	return { pos2D, glm::vec2{ pos2D + m_OriginalSize * glm::vec2{ scale.x, scale.y } } };
}
