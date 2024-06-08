#include "TransitionComponent.h"

#include <iostream>

#include "CollisionComponent.h"
#include "GameInstance.h"
#include "GameObject.h"
#include "SceneManager.h"

dae::TransitionComponent::TransitionComponent(GameObject* owner)
	:BaseComponent(owner)
{
}

void dae::TransitionComponent::Update(float deltaTime)
{
	m_ELapsedTime += deltaTime;
	if (m_ELapsedTime >= m_TransitionTime)
	{
		if (m_Reload)
		{
			GameInstance::GetInstance().ReloadLevel();
		}
		else if (!m_End)
		{
			GameInstance::GetInstance().LoadNextLevel();
		}
		else
		{
			GameInstance::GetInstance().EndGame();
		}
	}

}
