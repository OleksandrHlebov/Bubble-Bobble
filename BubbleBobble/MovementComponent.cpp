#include "MovementComponent.h"
#include "GameObject.h"
#include <algorithm>
#include "Collision2DComponent.h"
#include <functional>
#include "TileComponent.h"
#include "GridComponent.h"
#include "Scene.h"
#include "BubbleComponent.h"


void dae::MovementComponent::Start()
{
	GameEvent::Bind("OnOverlap", &m_OverlapHandler);
}

void dae::MovementComponent::AddMovementInput(const glm::vec3& inputVector)
{
	if (!m_IsEnabled)
		return;
	m_QueriedInput += inputVector;
	if (m_QueriedInput != glm::vec3{})
		m_Forward = m_QueriedInput;
}

void dae::MovementComponent::Jump()
{
	if (!m_IsEnabled)
		return;
	Scene* scene = GetOwner()->GetScene();
	Collision2DComponent* selfCollider = GetOwner()->GetComponent<Collision2DComponent>();
	const glm::vec2 center = selfCollider->GetCenter();
	auto [min, max] = selfCollider->GetBounds();
	min.y += DOWN_RAY_LENGTH;
	max.y += DOWN_RAY_LENGTH;
	m_IsGrounded = scene->TraceRect(min, max, false, true);
	if (!m_IsGrounded)
	{
		std::vector<GameObject*> toIgnore{ GetOwner() };
		Collision2DComponent* collider = scene->TraceRect(min, max, true, false, toIgnore);
		if (collider)
			m_IsGrounded = collider->GetOwner()->GetComponent<BubbleComponent>() != nullptr;
	}
	if (m_IsGrounded)
	{
		m_Velocity.y = -JumpHeight;
		GameEvent::Dispatch<OnJump>(GetOwner());
		m_IsGrounded = false;
	}
}

void dae::MovementComponent::Update(float deltaTime)
{
	if (!m_IsEnabled)
		return;
	const float gravity{ JumpHeight * 2.5f };
	if (deltaTime > .5f)
		return;

	GameObject* owner = GetOwner();
	Transform* transform = owner->GetComponent<Transform>();
	const float horizontalMovement{ m_QueriedInput.x * Speed }; // if positive check if moving right is allowed

	m_Velocity.x = horizontalMovement - horizontalMovement * InAirSlowdownPercent * (abs(m_Velocity.y) > FLT_EPSILON);
	m_Velocity.y = std::min(m_Velocity.y + gravity * deltaTime, GRAVITY_CLAMP);

	if (transform->GetWorldPosition().y > GetOwner()->GetScene()->GetLimits().y)
		transform->Move({ .0f, -transform->GetWorldPosition().y, .0f }, false);

	transform->Move(m_Velocity * deltaTime, true);
}

void dae::MovementComponent::LateUpdate(float)
{
	m_QueriedInput = glm::vec3{};
}

void dae::MovementComponent::HandleOverlapping(GameEvent* event)
{
	if (Collision2DComponent::OnOverlap* overlapEvent = static_cast<Collision2DComponent::OnOverlap*>(event))
	{
		// if second collider is static it means that first initiated the sweep
		// and is always first
		// dynamic collisions are being processed differently
		const bool isResultOfOwnSweep{ !overlapEvent->SecondCollider->IsDynamic() && GetOwner() == overlapEvent->First };
		if (isResultOfOwnSweep)
		{
			Collision2DComponent* selfCollider  = overlapEvent->FirstCollider;
			Collision2DComponent* otherCollider = overlapEvent->SecondCollider;
			auto [selfMin, selfMax]		= selfCollider->GetBounds();
			auto [otherMin, otherMax]	= otherCollider->GetBounds();
			glm::vec2 resolve{};

			if (overlapEvent->Overlap.x && overlapEvent->Overlap.x < overlapEvent->Overlap.y)
			{
				TileComponent* tileComp = overlapEvent->Second->GetComponent<TileComponent>();
				if (tileComp->HasTileAbove())
				{
					if (overlapEvent->Normal.x > 0)
						resolve.x = overlapEvent->Overlap.x;
					else
						resolve.x = -overlapEvent->Overlap.x;
				}
			}
			else
			{
				resolve.y = ResolveVerticalCollision(overlapEvent, isResultOfOwnSweep);
			}

			GetOwner()->GetComponent<Transform>()->Move({ resolve, .0f });
		}
		const bool collidedWithDynamic{ overlapEvent->SecondCollider->IsDynamic() && (overlapEvent->First == GetOwner() || overlapEvent->Second == GetOwner()) };
		if (collidedWithDynamic)
		{
			bool selfIsFirst{ overlapEvent->First == GetOwner() };
			GameObject* other	= (selfIsFirst) ? overlapEvent->Second : overlapEvent->First;
			const bool isOtherBubble{ static_cast<bool>(other->GetComponent<BubbleComponent>()) };
			if (isOtherBubble)
			{
				glm::vec2 resolve{};
				resolve.y = ResolveVerticalCollision(overlapEvent, selfIsFirst);
				GetOwner()->GetComponent<Transform>()->Move({ resolve, .0f });
			}
		}
	}
}

void dae::MovementComponent::End()
{
	using namespace std::placeholders;
	GameEvent::UnBind("OnOverlap", &m_OverlapHandler);
}

void dae::MovementComponent::SetEnabled(bool isEnabled)
{
	if (isEnabled == !m_IsEnabled)
	{
		if (isEnabled)
			GameEvent::Bind("OnOverlap", &m_OverlapHandler);
		else
			GameEvent::UnBind("OnOverlap", &m_OverlapHandler);
	}
	m_IsEnabled = isEnabled;
}

float dae::MovementComponent::ResolveVerticalCollision(Collision2DComponent::OnOverlap* overlapEvent, bool selfIsFirst)
{
	Collision2DComponent* selfCollider = (selfIsFirst) ? overlapEvent->FirstCollider : overlapEvent->SecondCollider;
	Collision2DComponent* otherCollider = (selfIsFirst) ? overlapEvent->SecondCollider : overlapEvent->SecondCollider;
	auto [selfMin, selfMax] = selfCollider->GetBounds();
	auto [otherMin, otherMax] = otherCollider->GetBounds();
	float resolve{};
	if (m_Velocity.y > .0f)
	{
		if (overlapEvent->Normal.y < 0)
		{
			if (overlapEvent->Overlap.y > RESOLVE_THRESHOLD)
			{
				resolve = -overlapEvent->Overlap.y;
				m_IsGrounded = otherMin.y < (selfMax.y + DOWN_RAY_LENGTH) && otherMax.y > selfMax.y;
			}
			if (m_IsGrounded)
				m_Velocity.y = std::min(m_Velocity.y, 0.f);
		}
	}
	return resolve;
}
