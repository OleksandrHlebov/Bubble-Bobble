#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		~SceneManager();

		Scene* CreateScene(const std::string& name);

		void Start();
		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render() const;
		void RenderUI() const;
		void ClearPendingDelete();

		void LoadScene(const std::string& name);

	private:
		SceneManager();
		friend class Singleton<SceneManager>;
		std::unordered_map<std::string, std::unique_ptr<Scene>> m_Scenes;
		Scene* m_CurrentScene{};
	};
}
