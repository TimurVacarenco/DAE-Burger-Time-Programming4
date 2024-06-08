#include "PlatformComponent.h"

#include <iostream>

#include "SceneManager.h"
#include "EnumClasses.h"
#include "GameObject.h"
#include "Scene.h"

bool dae::PlatformComponent::OnLeft(GameObject* go)
{
	if (!m_CheckedEdge)
	{
		CheckEdge();
	}
	if (m_IsLeftEdge)
	{
		return go->GetTransform()->GetWorldPosition().x - GetOwner()->GetTransform()->GetWorldPosition().x < 1;
	}
	return false;


}

bool dae::PlatformComponent::OnRight(GameObject* go)
{
	if (!m_CheckedEdge)
	{
		CheckEdge();
	}
	if (m_IsRightEdge)
	{
		return GetOwner()->GetTransform()->GetWorldPosition().x + 32 - go->GetTransform()->GetWorldPosition().x < 1;
	}
	return false;
}


void dae::PlatformComponent::CheckEdge()
{
	auto pos = GetOwner()->GetTransform()->GetWorldPosition();
	for (auto object : SceneManager::GetInstance().GetActiveScene().GetObjects())
	{
		if (object.get() != GetOwner() && object->GetTag() == Tag::platform)
		{
			auto otherpos = object->GetTransform()->GetWorldPosition();
			if (otherpos.y == pos.y)
			{
				if (otherpos.x == pos.x + 64)
				{
					m_IsRightEdge = false;
				}
				if (otherpos.x == pos.x - 64)
				{
					m_IsLeftEdge = false;
				}
			}
		}
	}
	m_CheckedEdge = true;
}

bool dae::PlatformComponent::OnBottom(GameObject* go)
{
	return GetOwner()->GetTransform()->GetWorldPosition().y + 54 - go->GetTransform()->GetWorldPosition().y < 1;
}

bool dae::PlatformComponent::InRange(GameObject* go) const
{
	return abs(go->GetTransform()->GetWorldPosition().y - (GetOwner()->GetTransform()->GetWorldPosition().y + 32)) < 12;
}

float dae::PlatformComponent::GetFloorY() const
{
	return GetOwner()->GetTransform()->GetWorldPosition().y + 32;
}

