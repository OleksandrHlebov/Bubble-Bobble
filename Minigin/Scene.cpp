#include "Scene.h"
#include "Render2DComponent.h"
#include "GameObject.h"

#include <algorithm>

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) 
{
}

Scene::~Scene() 
{}

void Scene::RemoveAllGameObjects()
{
	m_Objects.clear();
}

dae::GameObject* Scene::CreateGameObject()
{
	// if an object is created on execution of Start()
	// it modifies m_Objects array invalidating the for loop
	// to avoid it add all the objects created during that time to
	// pending and handle their start separately
	if (m_IsLoading)
	{
		const auto object = m_PendingObjects.insert(m_PendingObjects.end(), std::make_unique<GameObject>(this));
		return object->get();
	}
	const auto object = m_Objects.insert(m_Objects.end(), std::make_unique<GameObject>(this));
	if (m_IsLoaded)
		(*object)->Start();
	return (*object).get();
}

void Scene::Remove(GameObject* objectPtr)
{
	auto object = std::find_if(m_Objects.begin(), m_Objects.end(), [objectPtr](const auto& object) 
															{ return objectPtr == object.get(); });
	if (object != m_Objects.end())
		(*object)->Delete();
}

void Scene::Start()
{
	m_IsLoading = true;
	for (auto& object : m_Objects)
	{
		object->Start();
	}
	m_IsLoading = false;
	m_IsLoaded = true;
	for (auto& object : m_PendingObjects)
		object->Start();
	m_Objects.insert(m_Objects.end(), std::make_move_iterator(m_PendingObjects.begin())
									, std::make_move_iterator(m_PendingObjects.end()));
	m_PendingObjects.clear();
	if (m_ObjectsNeedReordering)
	{
		ReorderGameObjects_Internal();
		m_ObjectsNeedReordering = false;
	}
}

void dae::Scene::Update(float deltaTime)
{
	for(auto& object : m_Objects)
	{
		object->Update(deltaTime);
	}

	for (auto& object : m_Objects)
	{
		object->LateUpdate(deltaTime);
	}
	ClearPendingDelete();
}

void Scene::ReorderGameObjects_Internal()
{
	std::sort(m_Objects.begin(), m_Objects.end(),
			  [](auto& left, auto& right)
			  {
				  return static_cast<int>(left->GetRenderOrder()) < static_cast<int>(right->GetRenderOrder());
			  });
}

void Scene::ReorderGameObjects()
{
	// set datamember to true so if multiple objects need reordering
	// every object sets the order to the proper value before reordering takes place
	m_ObjectsNeedReordering = true;
}

void Scene::RenderUI()
{
	for (auto& object : m_Objects)
	{
		object->RenderUI();
	}
}

void Scene::ClearPendingDelete()
{
	std::erase_if(m_Objects, [](const auto& object) { return object->IsPendingDelete(); });
}

void Scene::FixedUpdate(float deltaTime)
{
	for (auto& object : m_Objects)
	{
		object->FixedUpdate(deltaTime);
	}
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

