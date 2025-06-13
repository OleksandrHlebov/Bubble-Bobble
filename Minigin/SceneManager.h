#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include "Singleton.h"
#include "GameEvent.h"

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
		void LoadScene(int id);
		void LoadScene_Impl(GameEvent*);

		Scene* GetCurrent() { return m_CurrentScene; }

	private:
		struct OnSceneChangeRequested final : public GameEvent
		{
			OnSceneChangeRequested(const std::string& name)
				: GameEvent("OnSceneChangeRequested", true)
				, Name{ name }
				{}
			const std::string Name;
		};
		EventHandler m_SceneChangeHandler{ std::bind(&SceneManager::LoadScene_Impl, this, std::placeholders::_1) };

		SceneManager();
		friend class Singleton<SceneManager>;
		std::unordered_map<std::string, std::unique_ptr<Scene>> m_Scenes;
		Scene* m_CurrentScene{};
	};
}
