#pragma once
#include "SceneManager.h"
#include <memory>

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

		const std::vector<Collision2DComponent*>& GetStaticCollisions() { return m_StaticColliders; }
		const std::vector<Collision2DComponent*>& GetDynamicCollisions() { return m_DynamicColliders; }

	private: 
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
