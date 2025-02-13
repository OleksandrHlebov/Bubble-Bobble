#pragma once
#include <memory>
#include "Transform.h"
#include "Component.h"
#include <unordered_set>

namespace dae
{
	class Texture2D;

	// todo: this should become final.
	class GameObject final
	{
	public:
		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render() const;

		void SetPosition(float x, float y);

		bool AddComponent(std::unique_ptr<Component> compUPtr);

		template<typename ComponentType>
		bool DeleteComponent()
		{
			auto comp = std::find_if(m_Components.begin(), m_Components.end(), [](const std::unique_ptr<Component>& compUPtr) 
																{ return dynamic_cast<ComponentType*>(compUPtr.get()) != nullptr; });
			m_Components.erase(comp);
			return false;
		}

		template<typename ComponentType>
		ComponentType* GetComponent() const
		{
			auto comp = std::find_if(m_Components.begin(), m_Components.end(), [](const std::unique_ptr<Component>& compUPtr) 
																{ return dynamic_cast<ComponentType*>(compUPtr.get()) != nullptr; });
			if (comp != m_Components.end())
				return static_cast<ComponentType*>((*comp).get());
			return (nullptr);
		}
		template<>
		Transform* GetComponent<Transform>() const
		{
			return m_TransformSPtr.get();
		}

	private:
		void RemovePendingDelete();

		std::unique_ptr<Transform> m_TransformSPtr{ std::make_unique<Transform>() };
		std::unordered_set<std::unique_ptr<Component>> m_Components;
	};

}
