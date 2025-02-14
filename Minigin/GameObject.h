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
		void Render() const;
		void Delete() { m_PendingDelete = true; }
		bool IsPendingDelete() { return m_PendingDelete; }

		void SetPosition(float x, float y);

		template<typename ComponentType, typename... Args>
		ComponentType* AddComponent(Args&&... args)
		{
			auto resultPair = m_Components.insert(std::make_unique<ComponentType>(std::forward<Args>(args)...));
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
		const ComponentType* GetComponent() const
		{
			auto comp = std::find_if(m_Components.begin(), m_Components.end(), [](const std::unique_ptr<Component>& compUPtr) 
																{ return dynamic_cast<ComponentType*>(compUPtr.get()) != nullptr; });
			if (comp != m_Components.end())
				return static_cast<ComponentType*>((*comp).get());
			return (nullptr);
		}
		template<>
		const Transform* GetComponent<Transform>() const
		{
			return &m_Transform;
		}

	private:
		void ClearPendingDelete();

		Transform m_Transform;
		std::unordered_set<std::unique_ptr<Component>> m_Components;

		bool m_PendingDelete{};
	};
}
