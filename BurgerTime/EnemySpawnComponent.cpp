#include "EnemySpawnComponent.h"

#include <iostream>

#include "CollisionComponent.h"
#include "EnemyComponent.h"
#include "GameInstance.h"
#include "GameObject.h"
#include "MrEgg.h"
#include "MrHotDog.h"
#include "MrPickle.h"
#include "Scene.h"
#include "SceneManager.h"
#include "EnumClasses.h"

dae::EnemySpawnComponent::EnemySpawnComponent(GameObject* owner)
	:BaseComponent(owner)
{
	m_ELapsedTime = m_TimePerSpawn;
}

void dae::EnemySpawnComponent::Update(float deltaTime)
{
	m_ELapsedTime += deltaTime;
	if (m_ELapsedTime >= m_TimePerSpawn)
	{
		m_ELapsedTime = 0;

		auto& scene = SceneManager::GetInstance().GetActiveScene();
		if (!m_Peter)
		{
			for (auto& obj : scene.GetObjects())
			{
				if (obj->GetTag() == Tag::peter)
					m_Peter = obj.get();
			}

		}

		if (m_Peter)
		{

			int random = 0;
			auto& pos = GetOwner()->GetTransform()->GetWorldPosition();

			if (GameInstance::GetInstance().GetGameMode() != GameMode::versus)
				random = rand() % 3;
			else
				random = rand() % 2;

			if (random == 0)
			{
				MrEgg{ scene,{pos.x,pos.y},m_Peter };
			}
			else if (random == 1)
			{
				MrPickle{ scene,{pos.x,pos.y},m_Peter };
			}
			else if (random == 2)
			{
				MrHotDog{ scene,{pos.x,pos.y},m_Peter };
			}
		}
		else
			m_ELapsedTime = m_TimePerSpawn;
	}

}
