#pragma once
#include "GameObject.h"
#include "SceneManager.h"

namespace dae
{
	class Scene final
	{
	public:
		explicit Scene(const std::string& name);

		GameObject* CreateGameObject();
		void Remove(GameObject* objectPtr);
		void RemoveAllGameObjects();

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render() const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 

		void ClearPendingDelete();

		std::string m_name;
		std::vector<std::unique_ptr<GameObject>> m_objects{};

		static unsigned int m_idCounter; 
	};

}
