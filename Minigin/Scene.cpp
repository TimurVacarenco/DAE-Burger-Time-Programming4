#include "Scene.h"

#include "GameObject.h"
#include "AnimationRenderComponent.h"

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::shared_ptr<GameObject> object)
{
	m_Objects.emplace_back(std::move(object));
}

void Scene::Add(const std::shared_ptr<GameObject>& object, int renderLayer)
{
	if (renderLayer == 0)
		m_ObjectsFirst.push_back(object);
	if (renderLayer == 1)
		m_ObjectsSecond.push_back(object);
	if (renderLayer >= 2)
		m_ObjectsThird.push_back(object);
	m_Objects.push_back(object);
}

void Scene::Remove(GameObject* object)
{
	m_ToRemove.push_back(object);
}

void Scene::RemoveAll()
{
	m_Objects.clear();
}

void Scene::FixedUpdate(float deltaTime)
{
	for (int i{}; i < (int)m_Objects.size(); ++i)
	{
		m_Objects[i]->FixedUpdate(deltaTime);
	}
}

void Scene::Update(float deltaTime)
{

	for (int i{}; i < (int)m_Objects.size(); ++i)
	{
		m_Objects[i]->Update(deltaTime);
	}
	DeleteObjects();
}

void Scene::Render() const
{
	for (const auto& object : m_ObjectsThird)
	{
		for (auto render : object->GetComponents<RenderComponent>())
		{
			render->Render();
		}

	}

	for (const auto& object : m_ObjectsSecond)
	{
		for (auto render : object->GetComponents<RenderComponent>())
		{
			render->Render();
		}

	}

	for (const auto& object : m_ObjectsFirst)
	{
		for (auto render : object->GetComponents<AnimationRenderComponent>())
		{
			render->Render();
		}

	}
}

void Scene::DeleteObjects()
{
	for (int j{}; j < (int)m_ToRemove.size(); ++j)
	{
		for (int i{}; i < (int)m_Objects.size(); ++i)
			if (m_Objects[i].get() == m_ToRemove[j])
				m_Objects.erase(m_Objects.begin() + i);
	}
	m_ToRemove.clear();
}