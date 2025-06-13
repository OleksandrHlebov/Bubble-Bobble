#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update(float deltaTime)
{
	m_CurrentScene->Update(deltaTime);
}

void dae::SceneManager::FixedUpdate(float deltaTime)
{
	m_CurrentScene->FixedUpdate(deltaTime);
}

void dae::SceneManager::Render() const
{
	m_CurrentScene->Render();
}

void dae::SceneManager::RenderUI() const
{
	m_CurrentScene->RenderUI();
}

void dae::SceneManager::ClearPendingDelete()
{
	m_CurrentScene->ClearPendingDelete();
}

void dae::SceneManager::LoadScene(const std::string& name)
{
	m_CurrentScene->End();
	m_CurrentScene = m_Scenes[name].get();
	m_CurrentScene->Start();
}

dae::SceneManager::SceneManager() = default;

dae::SceneManager::~SceneManager() = default;

dae::Scene* dae::SceneManager::CreateScene(const std::string& name)
{
	m_Scenes[name] = std::make_unique<Scene>(name);
	Scene* scene = m_Scenes[name].get();
	if (!m_CurrentScene)
		m_CurrentScene = scene;
	return scene;
}

void dae::SceneManager::Start()
{
	m_CurrentScene->Start();
}
