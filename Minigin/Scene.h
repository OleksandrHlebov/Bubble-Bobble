#pragma once
#include "SceneManager.h"
#include <memory>
#include <glm.hpp>
#include <utility>

namespace dae { class Collision2DComponent; }

namespace dae
{
	struct GameEvent;
	class GameObject;
	class Scene final
	{
	public:
		explicit Scene(const std::string& name);
		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) noexcept = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) noexcept = delete;

		GameObject* CreateGameObject();
		void Remove(GameObject* objectPtr);
		void RemoveAllGameObjects();

		void Start();
		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render() const;
		void RenderUI();
		void ReorderGameObjects();

		void AddCollider(Collision2DComponent* collider);

		Collision2DComponent* TraceRect(const glm::vec2& min, const glm::vec2& max, bool ignoreStatic = false, bool ignoreDynamic = false);
		std::vector<Collision2DComponent*> TraceRectMulti(const glm::vec2& min, const glm::vec2& max, bool ignoreStatic = false, bool ignoreDynamic = false);

		std::pair<Collision2DComponent*, glm::vec2> TraceSegment(const glm::vec2& begin, const glm::vec2& end, bool ignoreStatic = false, bool ignoreDynamic = false);
		std::pair<Collision2DComponent*, glm::vec2> TraceSegment(const glm::vec2& begin, const glm::vec2& direction, float length, bool ignoreStatic = false, bool ignoreDynamic = false);

		std::vector<std::pair<Collision2DComponent*, glm::vec2>> TraceSegmentMulti(const glm::vec2& begin, const glm::vec2& end, bool ignoreStatic = false, bool ignoreDynamic = false);
		std::vector<std::pair<Collision2DComponent*, glm::vec2>> TraceSegmentMulti(const glm::vec2& begin, const glm::vec2& direction, float length, bool ignoreStatic = false, bool ignoreDynamic = false);

		const std::vector<Collision2DComponent*>& GetStaticCollisions() { return m_StaticColliders; }
		const std::vector<Collision2DComponent*>& GetDynamicCollisions() { return m_DynamicColliders; }

	private: 
		std::pair<bool, glm::vec2> SegmentsIntersect(const glm::vec2& begin1, const glm::vec2& end1, const glm::vec2& begin2, const glm::vec2& end2);
		std::pair<bool, glm::vec2> SegmentIntersectsRect(const glm::vec2& begin, const glm::vec2& end, const glm::vec2& minAABB, const glm::vec2& maxAABB);
		float OrientationToSegment(const glm::vec2& of, const glm::vec2& toBegin, const glm::vec2& toEnd);
		bool RectsIntersect(const glm::vec2& min1, const glm::vec2& max1, const glm::vec2& min2, const glm::vec2& max2);
		void ClearPendingDelete();
		void ReorderGameObjects_Internal();

		std::string m_name;
		std::vector<std::unique_ptr<GameObject>> m_Objects;
		std::vector<std::unique_ptr<GameObject>> m_PendingObjects;
		std::vector<Collision2DComponent*> m_StaticColliders;
		std::vector<Collision2DComponent*> m_DynamicColliders;

		static unsigned int m_idCounter; 
		bool m_IsLoaded{};
		bool m_IsLoading{};
		bool m_ObjectsNeedReordering{};
	};

}
