#pragma once
#include <memory>
#include "Component.h"
#include "Transform.h"
#include <unordered_set>
#include "GameEvent.h"
#include <type_traits>
#include "RenderPriorities.h"


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
		const GameObject* GetParent() const { return m_ParentPtr; }
		Scene* GetScene() { return m_ScenePtr; }

		uint32_t GetID() { return m_ID; }

		void SetLocalPosition(float x, float y);
		void SetLocalPosition(const glm::vec3& pos);
		void SetScale(const glm::vec3& scale) { m_Transform.SetScale(scale); }
		void SetScale(float x, float y, float z) { m_Transform.SetScale(x, y, z); }

		// supported only on scene load
		// reordering happens after start is executed
		void SetRenderPriority(int renderPriority);
		void SetRenderPriority(RenderPriority renderPriority);

		int GetRenderPriority() { return m_RenderPriority; }

		const glm::vec3& GetWorldPosition();
		const glm::vec3& GetLocalPosition() { return m_Transform.GetLocalPosition(); }
		const glm::vec3& GetScale() const { return m_Transform.GetScale(); }

		template<typename ComponentType, typename... Args>
		ComponentType* AddComponent(Args&&... args)
		{
			auto& result = m_Components.emplace_back(std::make_unique<ComponentType>(std::forward<Args>(args)..., this));
			if (m_IsInitialised)
				result->Start();
			return static_cast<ComponentType*>(result.get());
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
		const ComponentType* GetComponent() const
		{
			return GetComponent_Impl<ComponentType>(*this);
		}

		template<typename ComponentType>
		ComponentType* GetComponent()
		{
			return GetComponent_Impl<ComponentType>(*this);
		}

		void ClearPendingDelete();

	private:

		template<typename ComponentType, typename T>
		static auto GetComponent_Impl(T& t) -> decltype(t.GetComponent<ComponentType>())
		{
			if constexpr (std::is_same_v<std::remove_cv_t<ComponentType>, Transform>)
			{
				return &t.m_Transform;
			}
			else
			{
				auto comp = std::find_if(t.m_Components.begin(), t.m_Components.end(), [](const std::unique_ptr<Component>& compUPtr)
										 { return dynamic_cast<ComponentType*>(compUPtr.get()) != nullptr; });
				if (comp != t.m_Components.end())
					return static_cast<ComponentType*>((*comp).get());
				return (nullptr);
			}
		}

		void RemoveChild(GameObject* child);

		Scene* m_ScenePtr;

		GameObject* m_ParentPtr{ nullptr };
		std::vector<GameObject*> m_Children;

		Transform m_Transform{ this };
		std::vector<std::unique_ptr<Component>> m_Components;

		inline static uint32_t m_InstanceCounter{};
		uint32_t m_ID{ m_InstanceCounter++ };
		int m_RenderPriority{ 0 };

		bool m_PendingDelete{};
		bool m_IsInitialised{};
	};
}
