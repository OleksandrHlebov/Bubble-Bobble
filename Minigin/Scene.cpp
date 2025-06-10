#include "Scene.h"
#include "Render2DComponent.h"
#include "GameObject.h"

#include <algorithm>
#include "Collision2DComponent.h"
#include "MathHelpers.h"

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) 
{
}

Scene::~Scene() 
{}

void Scene::RemoveAllGameObjects()
{
	m_Objects.clear();
}

dae::GameObject* dae::Scene::CreateGameObject()
{
	// if an object is created on execution of Start()
	// it modifies m_Objects array invalidating the for loop
	// to avoid it add all the objects created during that time to
	// pending and handle their start separately
	if (m_IsLoading)
	{
		const auto object = m_PendingObjects.insert(m_PendingObjects.end(), std::make_unique<GameObject>(this));
		return object->get();
	}
	const auto object = m_Objects.insert(m_Objects.end(), std::make_unique<GameObject>(this));
	if (m_IsLoaded)
		(*object)->Start();
	return (*object).get();
}

void Scene::Remove(GameObject* objectPtr)
{
	auto object = std::find_if(m_Objects.begin(), m_Objects.end(), [objectPtr](const auto& object) 
															{ return objectPtr == object.get(); });
	if (object != m_Objects.end())
		(*object)->Delete();
}

void Scene::Start()
{
	m_IsLoading = true;
	for (auto& object : m_Objects)
	{
		object->Start();
	}
	m_IsLoading = false;
	m_IsLoaded = true;
	for (auto& object : m_PendingObjects)
		object->Start();
	m_Objects.insert(m_Objects.end(), std::make_move_iterator(m_PendingObjects.begin())
									, std::make_move_iterator(m_PendingObjects.end()));
	m_PendingObjects.clear();
	if (m_ObjectsNeedReordering)
	{
		ReorderGameObjects_Internal();
		m_ObjectsNeedReordering = false;
	}
}

void dae::Scene::Update(float deltaTime)
{
	for(auto& object : m_Objects)
	{
		object->Update(deltaTime);
	}

	for (auto& object : m_Objects)
	{
		object->LateUpdate(deltaTime);
	}
	ClearPendingDelete();
}

std::vector<std::pair<dae::Collision2DComponent*, glm::vec2>> Scene::TraceSegmentMulti(const glm::vec2& begin, const glm::vec2& end, bool ignoreStatic, bool ignoreDynamic)
{
	assert(ignoreStatic != true && ignoreDynamic != true && "Ignoring every collider for trace segment");
	std::vector<std::pair<dae::Collision2DComponent*, glm::vec2>> output;
	static const size_t ESTIMATE_MAX_COLLISIONS{ 32 };
	output.reserve(ESTIMATE_MAX_COLLISIONS);
	if (!ignoreStatic)
		for (Collision2DComponent* collider : m_StaticColliders)
		{
			const auto [min, max] = collider->GetBounds();
			if (auto [intersects, intersection] = SegmentIntersectsRect(begin, end, min, max); intersects)
				output.emplace_back(collider, std::move(intersection));
		}
	if (!ignoreDynamic)
		for (Collision2DComponent* collider : m_DynamicColliders)
		{
			const auto [min, max] = collider->GetBounds();
			if (auto [intersects, intersection] = SegmentIntersectsRect(begin, end, min, max); intersects)
				output.emplace_back(collider, std::move(intersection));
		}
	return std::move(output);
}

std::vector<std::pair<dae::Collision2DComponent*, glm::vec2>> Scene::TraceSegmentMulti(const glm::vec2& begin, const glm::vec2& direction, float length, bool ignoreStatic, bool ignoreDynamic)
{
	return TraceSegmentMulti(begin, begin + direction * length, ignoreStatic, ignoreDynamic);
}

std::pair<bool, glm::vec2> Scene::SegmentIntersectsRect(const glm::vec2& begin, const glm::vec2& end, const glm::vec2& minAABB, const glm::vec2& maxAABB)
{
	const glm::vec2 topLeft		{ minAABB.x, minAABB.y };
	const glm::vec2 bottomLeft	{ minAABB.x, maxAABB.y };
	const glm::vec2 topRight	{ maxAABB.x, minAABB.y };
	const glm::vec2 bottomRight	{ maxAABB.x, maxAABB.y };

	if (auto [intersects, intersection] = SegmentsIntersect(begin, end, topLeft, bottomLeft); intersects)
		return { true, std::move(intersection) };
	if (auto [intersects, intersection] = SegmentsIntersect(begin, end, topLeft, topRight); intersects)
		return { true, std::move(intersection) };
	if (auto [intersects, intersection] = SegmentsIntersect(begin, end, bottomRight, bottomLeft); intersects)
		return { true, std::move(intersection) };
	if (auto [intersects, intersection] = SegmentsIntersect(begin, end, bottomRight, topRight); intersects)
		return { true, std::move(intersection) };

	return { false, glm::vec2{} };
}

std::pair<bool, glm::vec2> Scene::SegmentsIntersect(const glm::vec2& begin1, const glm::vec2& end1, const glm::vec2& begin2, const glm::vec2& end2)
{
	// https://stackoverflow.com/questions/3746274/line-intersection-with-aabb-rectangle/3746601#3746601
	const glm::vec2 a = end1 - begin1;
	const glm::vec2 b = end2 - begin2;
	const float denom = dae::Cross2D(a, b);

	if (abs(denom) < FLT_EPSILON)
		return { false, glm::vec2{} };

	const glm::vec2 c = begin2 - begin1;
	const float t = dae::Cross2D(c, b) / denom;
	if (t < 0 || t > 1)
		return { false, glm::vec2{} };

	const float u = dae::Cross2D(c, a) / denom;
	if (u < 0 || u > 1)
		return { false, glm::vec2{} };

	return { true, begin1 + t * a };
}

std::pair<Collision2DComponent*, glm::vec2> Scene::TraceSegment(const glm::vec2& begin, const glm::vec2& end, bool ignoreStatic, bool ignoreDynamic)
{
	assert(ignoreStatic != true && ignoreDynamic != true && "Ignoring every collider for trace segment");
	if (!ignoreStatic)
		for (Collision2DComponent* collider : m_StaticColliders)
		{
			const auto [min, max] = collider->GetBounds();
			if (auto [intersects, intersection] = SegmentIntersectsRect(begin, end, min, max); intersects)
				return { collider, std::move(intersection) };
		}
	if (!ignoreDynamic)
		for (Collision2DComponent* collider : m_DynamicColliders)
		{
			const auto [min, max] = collider->GetBounds();
			if (auto [intersects, intersection] = SegmentIntersectsRect(begin, end, min, max); intersects)
				return { collider, std::move(intersection) };
		}
	return { nullptr, glm::vec2{} };
}

std::pair<Collision2DComponent*, glm::vec2> Scene::TraceSegment(const glm::vec2& begin, const glm::vec2& direction, float length, bool ignoreStatic, bool ignoreDynamic)
{
	return TraceSegment(begin, begin + direction * length, ignoreStatic, ignoreDynamic);
}

void Scene::AddCollider(Collision2DComponent* collider)
{
	if (collider->IsDynamic())
		m_DynamicColliders.emplace_back(collider);
	else
		m_StaticColliders.emplace_back(collider);
}

void Scene::ReorderGameObjects_Internal()
{
	std::sort(m_Objects.begin(), m_Objects.end(),
			  [](auto& left, auto& right)
			  {
				  return left->GetRenderPriority() < right->GetRenderPriority();
			  });
}

void Scene::ReorderGameObjects()
{
	// set datamember to true so if multiple objects need reordering
	// every object sets the order to the proper value before reordering takes place
	m_ObjectsNeedReordering = true;
}

void Scene::RenderUI()
{
	for (auto& object : m_Objects)
	{
		object->RenderUI();
	}
}

void Scene::ClearPendingDelete()
{
	std::erase_if(m_Objects, [](const auto& object) { return object->IsPendingDelete(); });
}

void Scene::FixedUpdate(float deltaTime)
{
	for (auto& object : m_Objects)
	{
		object->FixedUpdate(deltaTime);
	}
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

