#include "TransformComponent.h"

#include "GameObject.h"

dae::TransformComponent::TransformComponent(GameObject* obj)
	:BaseComponent(obj) {}

const Vector3& dae::TransformComponent::GetLocalPosition() const
{
	return m_LocalPosition;
}

const Vector3& dae::TransformComponent::GetWorldPosition()
{

	if (m_IsDirty)
	{
		UpdateWorldPosition();
	}

	return m_WorldPosition;
}


void dae::TransformComponent::SetLocalPosition(const float x, const float y, const float z)
{

	m_LocalPosition.x = x;
	m_LocalPosition.y = y;
	m_LocalPosition.z = z;

	SetDirty();
}

void dae::TransformComponent::SetLocalPosition(const Vector3& pos)
{
	SetLocalPosition(pos.x, pos.y, pos.z);
}

void dae::TransformComponent::UpdateWorldPosition()
{
	GameObject* owner = GetOwner();

	if (owner->GetParent() == nullptr)
	{
		m_WorldPosition = m_LocalPosition;
	}
	else
	{
		auto parentPos = owner->GetParent()->GetTransform()->GetWorldPosition();
		m_WorldPosition.x = parentPos.x + m_LocalPosition.x;
		m_WorldPosition.y = parentPos.y + m_LocalPosition.y;
		m_WorldPosition.z = parentPos.z + m_LocalPosition.z;
		if (m_WorldPosition.x > 600)
		{
			m_WorldPosition = m_WorldPosition;
		}

	}
	m_IsDirty = false;
}

void dae::TransformComponent::SetDirty()
{
	m_IsDirty = true;
	auto childrenVec = GetOwner()->GetChildren();
	for (auto child : childrenVec)
	{
		child->GetTransform()->SetDirty();
	}
}
