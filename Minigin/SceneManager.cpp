#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update(float deltaTime)
{
	for(auto& scene : m_Scenes)
	{
		scene->Update(deltaTime);
	}
}

void dae::SceneManager::FixedUpdate(float deltaTime)
{
	for (auto& scene : m_Scenes)
	{
		scene->FixedUpdate(deltaTime);
	}
}

void dae::SceneManager::Render() const
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}
}

void dae::SceneManager::RenderUI() const
{
	for (const auto& scene : m_Scenes)
	{
		scene->RenderUI();
	}
}

void dae::SceneManager::ClearPendingDelete()
{
	for (const auto& scene : m_Scenes)
	{
		scene->ClearPendingDelete();
	}
}

dae::SceneManager::SceneManager() = default;

dae::SceneManager::~SceneManager() = default;

dae::Scene* dae::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = m_Scenes.insert(m_Scenes.end(), std::make_unique<Scene>(name));
	return (*scene).get();
}

void dae::SceneManager::Start()
{
	for (const auto& scene : m_Scenes)
	{
		scene->Start();
	}	
}
