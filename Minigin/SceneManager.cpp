#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update(float deltaTime)
{
	for(auto& scene : m_scenes)
	{
		scene->Update(deltaTime);
	}
}

void dae::SceneManager::FixedUpdate(float deltaTime)
{
	for (auto& scene : m_scenes)
	{
		scene->FixedUpdate(deltaTime);
	}
}

void dae::SceneManager::Render() const
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

void dae::SceneManager::RenderUI() const
{
	for (const auto& scene : m_scenes)
	{
		scene->RenderUI();
	}
}

dae::SceneManager::SceneManager() = default;

dae::SceneManager::~SceneManager() = default;

dae::Scene* dae::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = m_scenes.insert(m_scenes.end(), std::make_unique<Scene>(name));
	return (*scene).get();
}

void dae::SceneManager::Start()
{
	for (const auto& scene : m_scenes)
	{
		scene->Start();
	}	
}
