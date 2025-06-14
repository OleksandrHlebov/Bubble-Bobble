#include "SceneManager.h"
#include "Scene.h"
#include "GameEvent.h"
#include "InputManager.h"

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

bool dae::SceneManager::LoadScene(const std::string& name)
{
	if (!m_Scenes.contains(name))
	{
		std::cout << "scene not found name: " << name << std::endl;
		return false;
	}
	GameEvent::Dispatch<OnSceneChangeRequested>(name);
	return true;
}

bool dae::SceneManager::LoadScene(int id)
{
	if (m_CurrentScene->GetID() == id)
		return false;
	for (auto& [name, scene] : m_Scenes)
	{
		if (scene->GetID() == id)
		{
			GameEvent::Dispatch<OnSceneChangeRequested>(name);
			return true;
		}
	}
	std::cout << "scene not found id: " << id << std::endl;
	return false;
}

void dae::SceneManager::LoadScene_Impl(GameEvent* event)
{
	auto change = static_cast<OnSceneChangeRequested*>(event);
	Scene* newScene = m_Scenes[change->Name].get();
	if (newScene->GetID() == m_CurrentScene->GetID())
		return;
	m_CurrentScene->End();
	m_CurrentScene = newScene;
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
	GameEvent::Bind("OnSceneChangeRequested", &m_SceneChangeHandler);
	m_CurrentScene->Start();
}
