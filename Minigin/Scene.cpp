#include "Scene.h"
#include "Render2DComponent.h"

#include <algorithm>

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

void Scene::RemoveAllGameObjects()
{
	m_objects.clear();
}

dae::GameObject* Scene::CreateGameObject()
{
	const auto object = m_objects.insert(m_objects.end(), std::make_unique<GameObject>());
	return (*object).get();
}

void Scene::Remove(GameObject* objectPtr)
{
	m_objects.erase(std::find_if(m_objects.begin(), m_objects.end(), [objectPtr](const auto& object) 
													{ return objectPtr == object.get(); }));
}

void dae::Scene::Update(float deltaTime)
{
	for(auto& object : m_objects)
	{
		object->Update(deltaTime);
	}
}

void Scene::FixedUpdate(float deltaTime)
{
	for (auto& object : m_objects)
	{
		object->FixedUpdate(deltaTime);
	}
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}

