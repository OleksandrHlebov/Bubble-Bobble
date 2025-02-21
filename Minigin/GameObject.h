#pragma once
#include <memory>
#include "Component.h"
#include "Transform.h"
#include <unordered_set>

namespace dae
{
	class Texture2D;
	class GameObject final
	{
	public:
		GameObject() = default;
		~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render();
		void Delete() { m_PendingDelete = true; }
		bool IsPendingDelete() { return m_PendingDelete; }

		void SetParent(GameObject* parent, bool keepWorldPosition = false);
		void AddChild(GameObject* child);
		void RemoveChild(GameObject* child);

		bool HasAsParent(GameObject* object);
		bool IsChildOf(GameObject* object);

		GameObject* GetParent() { return m_ParentPtr; };

		void SetLocalPosition(float x, float y);
		void SetLocalPosition(const glm::vec3& pos);

		const glm::vec3& GetWorldPosition() { return m_Transform.GetWorldPosition(); };
		const glm::vec3& GetLocalPosition() { return m_Transform.GetLocalPosition(); };

		template<typename ComponentType, typename... Args>
		ComponentType* AddComponent(Args&&... args)
		{
			auto resultPair = m_Components.insert(std::make_unique<ComponentType>(std::forward<Args>(args)..., this));
			return static_cast<ComponentType*>((*resultPair.first).get());
		}

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

		GameObject* m_ParentPtr{ nullptr };
		std::unordered_set<GameObject*> m_Children;

		Transform m_Transform{ this };
		std::unordered_set<std::unique_ptr<Component>> m_Components;

		bool m_PendingDelete{};
	};
}
