#pragma once
#include <memory>
#include "Component.h"
#include "Transform.h"
#include <unordered_set>


namespace dae
{
	class Scene;
	class Controller;
	class Texture2D;
	class GameObject final
	{
	public:
		GameObject(Scene* scene);
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Start();
		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void LateUpdate(float deltaTime);
		void Render();
		void RenderUI();
		void End();

		void Delete();
		bool IsPendingDelete() { return m_PendingDelete; }
		bool IsPositionDirty();
		void InvalidatePositionsOfChildren();

		void AttachTo(GameObject* parent, bool keepWorldPosition = false);

		bool HasAsParent(GameObject* object);
		bool IsChildOf(GameObject* object);

		GameObject* GetParent() { return m_ParentPtr; }
		Scene* GetScene() { return m_ScenePtr; }

		uint32_t GetID() { return m_ID; }

		void SetLocalPosition(float x, float y);
		void SetLocalPosition(const glm::vec3& pos);
		void SetScale(const glm::vec3& scale) { m_Transform.SetScale(scale); }
		void SetScale(float x, float y, float z) { m_Transform.SetScale(x, y, z); }

		const glm::vec3& GetWorldPosition();
		const glm::vec3& GetLocalPosition() { return m_Transform.GetLocalPosition(); }
		const glm::vec3& GetScale() { return m_Transform.GetScale(); }

		template<typename ComponentType, typename... Args>
		ComponentType* AddComponent(Args&&... args)
		{
			auto resultPair = m_Components.insert(std::make_unique<ComponentType>(std::forward<Args>(args)..., this));
			if (m_IsInitialised)
				(*resultPair.first).get()->Start();
			return static_cast<ComponentType*>((*resultPair.first).get());
		}

		std::vector<GameObject*>& GetChildren() { return m_Children; }

		template<typename ComponentType>
		bool DeleteComponent()
		{
			auto comp = std::find_if(m_Components.begin(), m_Components.end(), [](const std::unique_ptr<Component>& compUPtr) 
																{ return dynamic_cast<ComponentType*>(compUPtr.get()) != nullptr; });
			(*comp)->Delete();
			return false;
		}

		template<typename ComponentType>
		ComponentType* GetComponent()
		{
			auto comp = std::find_if(m_Components.begin(), m_Components.end(), [](const std::unique_ptr<Component>& compUPtr) 
																{ return dynamic_cast<ComponentType*>(compUPtr.get()) != nullptr; });
			if (comp != m_Components.end())
				return static_cast<ComponentType*>((*comp).get());
			return (nullptr);
		}
		template<>
		Transform* GetComponent<Transform>()
		{
			return &m_Transform;
		}

	private:
		void ClearPendingDelete();
		void RemoveChild(GameObject* child);

		Scene* m_ScenePtr;

		GameObject* m_ParentPtr{ nullptr };
		std::vector<GameObject*> m_Children;

		Transform m_Transform{ this };
		std::unordered_set<std::unique_ptr<Component>> m_Components;

		inline static uint32_t m_InstanceCounter{};
		uint32_t m_ID{ m_InstanceCounter++ };

		bool m_PendingDelete{};
		bool m_IsInitialised{};
	};
}
