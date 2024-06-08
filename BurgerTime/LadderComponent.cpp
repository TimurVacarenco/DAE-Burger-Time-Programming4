#include "LadderComponent.h"
#include <Structs.h>
#include "GameObject.h"
#include "SceneManager.h"
#include "Scene.h"
#include "EnumClasses.h"

bool dae::LadderComponent::OnTop(GameObject* go)
{
	if (IsTop()) 
	{
		return GetOwner()->GetTransform()->GetWorldPosition().y - go->GetTransform()->GetWorldPosition().y > 30;
	}
	return false;
}

bool dae::LadderComponent::OnBottom(GameObject* go)
{
	if (IsBottom())
	{
		return GetOwner()->GetTransform()->GetWorldPosition().y + 32 - go->GetTransform()->GetWorldPosition().y < 2;
	}
	return go->GetTransform()->GetWorldPosition().y - GetOwner()->GetTransform()->GetWorldPosition().y > 63;
}

bool dae::LadderComponent::IsBottom()
{
    if (!m_CheckedPos)
    {
        CheckPos();
    }
    return m_IsBottom;
}

bool dae::LadderComponent::IsTop()
{
    if (!m_CheckedPos)
    {
        CheckPos();
    }
    return m_IsTop;
}

bool dae::LadderComponent::InRange(GameObject* go)
{
	return abs(go->GetTransform()->GetWorldPosition().x - GetOwner()->GetTransform()->GetWorldPosition().x) < m_ClimbRange;
}

void dae::LadderComponent::CheckPos()
{
	Vector3 pos = GetOwner()->GetTransform()->GetWorldPosition();
	for (auto object : SceneManager::GetInstance().GetActiveScene().GetObjects())
	{
		if (object.get() != GetOwner() && object->GetTag() == Tag::ladder)
		{
			auto otherpos = object->GetTransform()->GetWorldPosition();
			if (otherpos.x == pos.x)
			{
				if (otherpos.y == pos.y + 64)
				{
					m_IsBottom = false;
				}
				if (otherpos.y == pos.y - 64)
				{
					m_IsTop = false;
				}
			}
		}
	}
	m_CheckedPos = true;
}
