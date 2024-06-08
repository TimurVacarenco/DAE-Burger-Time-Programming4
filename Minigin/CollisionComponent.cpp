#include "CollisionComponent.h"

#include <glm/vec3.hpp>
#include "GameObject.h"

bool dae::CollisionComponent::IsOverlapping(GameObject* other)
{
	if (GetOwner() == other )
		return false;

	if (auto otherCol = other->GetComponent<CollisionComponent>())
	{
		auto pos = GetOwner()->GetTransform()->GetLocalPosition();
		pos.x += m_OffsetX;
		pos.y += m_OffsetY;
		glm::vec3 cornerpos{ pos.x + m_Width,pos.y + m_Height,pos.z };

		auto otherPos = other->GetTransform()->GetLocalPosition();
		otherPos.x += otherCol->m_OffsetX;
		otherPos.y += otherCol->m_OffsetY;
		glm::vec3 otherCorner{ otherPos.x + otherCol->m_Width,otherPos.y + otherCol->m_Height,otherPos.z };

		if (pos.x > otherCorner.x || otherPos.x > cornerpos.x)
		{
			return false;
		}
		if (cornerpos.y < otherPos.y || otherCorner.y < pos.y)
		{
			return false;
		}
		return true;
	}
	return false;
}


bool dae::CollisionComponent::IsOverlapping(Rect other)
{
	auto pos = GetOwner()->GetTransform()->GetLocalPosition();
	pos.x += m_OffsetX;
	pos.y += m_OffsetY;
	glm::vec3 cornerPos{ pos.x + m_Width,pos.y + m_Height,pos.z };
	glm::vec3 otherPos = { other.x,other.y,0 };
	glm::vec3 otherCorner = { other.x + other.width,other.y + other.height,0 };

	if (pos.x > otherCorner.x || otherPos.x > cornerPos.x)
	{
		return false;
	}
	if (cornerPos.y < otherPos.y || otherCorner.y < pos.y)
	{
		return false;
	}
	return true;
}

void dae::CollisionComponent::SetSize(float width, float height)
{
	m_Width = width;
	m_Height = height;
}

bool dae::CollisionComponent::IsUnder(GameObject* other)
{
	if (GetOwner() == other)
	{
		return false;
	}
	auto pos = GetOwner()->GetTransform()->GetLocalPosition();
	pos.x += m_OffsetX;
	pos.y += m_OffsetY;
	glm::vec3 cornerPos{ pos.x + m_Width,pos.y + m_Height,pos.z };
	auto otherCol = other->GetComponent<CollisionComponent>();
	auto otherPos = other->GetTransform()->GetLocalPosition();
	otherPos.x += otherCol->m_OffsetX;
	otherPos.y += otherCol->m_OffsetY;
	glm::vec3 otherCorner{ otherPos.x + otherCol->m_Width,otherPos.y + otherCol->m_Height,otherPos.z };


	if (cornerPos.y > otherCorner.y)
	{
		return true;
	}
	return false;
}

bool dae::CollisionComponent::IsUnder(Rect other)
{
	auto pos = GetOwner()->GetTransform()->GetLocalPosition();
	pos.x += m_OffsetX;
	pos.y += m_OffsetY;
	glm::vec3 cornerPos{ pos.x + m_Width,pos.y + m_Height,pos.z };

	glm::vec3 otherCorner = { other.x + other.width,other.y + other.height,0 };

	if (cornerPos.y < otherCorner.y)
	{
		return true;
	}
	return false;
}

bool dae::CollisionComponent::IsToSide(GameObject* other)
{
	if (GetOwner() == other)
	{
		return false;
	}
	auto pos = GetOwner()->GetTransform()->GetLocalPosition();
	pos.x += m_OffsetX;
	pos.y += m_OffsetY;
	glm::vec3 cornerPos{ pos.x + m_Width,pos.y + m_Height,pos.z };
	auto otherCol = other->GetComponent<CollisionComponent>();
	auto otherPos = other->GetTransform()->GetLocalPosition();
	otherPos.x += otherCol->m_OffsetX;
	otherPos.y += otherCol->m_OffsetY;
	glm::vec3 otherCorner{ otherPos.x + otherCol->m_Width,otherPos.y + otherCol->m_Height,otherPos.z };


	if (cornerPos.x > otherCorner.x || otherPos.x > pos.x)
	{
		return true;
	}
	return false;
}

bool dae::CollisionComponent::IsToSide(Rect other)
{
	auto pos = GetOwner()->GetTransform()->GetLocalPosition();
	pos.x += m_OffsetX;
	pos.y += m_OffsetY;
	glm::vec3 cornerPos{ pos.x + m_Width,pos.y + m_Height,pos.z };

	glm::vec3 otherPos{ other.x,other.y,0 };
	glm::vec3 otherCorner = { other.x + other.width,other.y + other.height,0 };

	if (pos.x > otherPos.x || cornerPos.x < otherCorner.x)
	{
		return true;
	}
	return false;
}