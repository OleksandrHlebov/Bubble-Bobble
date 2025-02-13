#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		~SceneManager();

		Scene* CreateScene(const std::string& name);

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render() const;

	private:
		SceneManager();
		friend class Singleton<SceneManager>;
		std::vector<std::unique_ptr<Scene>> m_scenes;
	};
}
