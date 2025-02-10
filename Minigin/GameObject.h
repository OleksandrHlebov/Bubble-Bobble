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
		virtual void Update(float deltaTime);
		virtual void FixedUpdate(float deltaTime);
		virtual void Render() const;

		void SetPosition(float x, float y);
		
		void AddComponent(std::shared_ptr<Component> compUPtr);

		template<typename ComponentType>
		std::shared_ptr<ComponentType> GetComponent()
		{
			for (auto& comp : m_Components)
				if (auto searchedComp = dynamic_pointer_cast<ComponentType>(comp))
					return searchedComp;
			return (nullptr);
		}
		template<>
		std::shared_ptr<Transform> GetComponent<Transform>()
		{
			return m_TransformSPtr;
		}

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::shared_ptr<Transform> m_TransformSPtr{ std::make_shared<Transform>() };
		std::unordered_set<std::shared_ptr<Component>> m_Components;
	};

}
