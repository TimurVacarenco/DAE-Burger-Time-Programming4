#include "PepperComponent.h"

#include <iostream>

#include "AnimationRenderComponent.h"
#include "CollisionComponent.h"
#include "GameObject.h"
#include "PlatformComponent.h"
#include "Scene.h"
#include "SceneManager.h"

dae::PepperComponent::PepperComponent(GameObject* owner)
	:BaseComponent(owner)
{
}
void dae::PepperComponent::Update(float deltaTime)
{
	
	HandleMovement(deltaTime);
	HandleCollision(deltaTime);
	HandleAnim();

}
void dae::PepperComponent::InitAnimation(AnimationRenderComponent* comp)
{
	if (comp == nullptr)
		return;

	m_Anim = comp;

	m_Idle = m_Anim->AddClip(1, false);
	m_RunLeft = m_Anim->AddClip(3, true);
	m_RunRight = m_Anim->AddClip(3, true);
	m_Climb = m_Anim->AddClip(3, true);
	m_ClimbDown = m_Anim->AddClip(3, true);
}
void dae::PepperComponent::HandleMovement(float deltaTime)
{
	auto pos = GetOwner()->GetTransform()->GetLocalPosition();
	m_OnPlatform = false;
	m_OnLadder = false;
	float ladderX{};
	float platformY{};

	for (auto& obj : SceneManager::GetInstance().GetActiveScene().GetObjects())
	{
		if (GetOwner()->GetComponent<CollisionComponent>()->IsOverlapping(obj.get()))
			if (obj->GetTag()==Tag::platform)
			{
				if (!GetOwner()->GetComponent<CollisionComponent>()->IsUnder(obj.get()))
				{
					m_OnPlatform = true;
					platformY = obj->GetComponent<PlatformComponent>()->GetFloorPos().y;
				}
			}
			else if (obj->GetTag() == Tag::ladder)
			{
				ladderX = obj->GetTransform()->GetLocalPosition().x;

				if (abs(ladderX - GetOwner()->GetTransform()->GetLocalPosition().x) < 10.f)
				{
					m_OnLadder = true;

				}

			}
	}

	switch (m_State)
	{
	case CharacterState::idle:
		break;
	case CharacterState::left:
		if (!m_OnPlatform)
			return;
		pos.x -= m_Speed * deltaTime;
		pos.y = platformY + 60;
		GetOwner()->GetTransform()->SetLocalPosition(pos.x, pos.y, pos.z);
		break;
	case CharacterState::right:
		if (!m_OnPlatform)
			return;
		pos.x += m_Speed * deltaTime;
		pos.y = platformY + 60;
		GetOwner()->GetTransform()->SetLocalPosition(pos.x, pos.y, pos.z);
		break;
	case CharacterState::up:
		if (!m_OnLadder)
			return;
		pos.y -= m_LadderSpeed * deltaTime;
		GetOwner()->GetTransform()->SetLocalPosition(ladderX, pos.y, pos.z);
		break;
	case CharacterState::down:
		if (!m_OnLadder)
			return;
		pos.y += m_LadderSpeed * deltaTime;
		GetOwner()->GetTransform()->SetLocalPosition(ladderX, pos.y, pos.z);
		break;
	}
}

void dae::PepperComponent::HandleCollision(float deltaTime)
{
	auto pos = GetOwner()->GetTransform()->GetLocalPosition();
	m_Colliding = false;
	bool underLadder = false;
	int ladders = 0;

	for (auto& obj : SceneManager::GetInstance().GetActiveScene().GetObjects())
	{
		if (GetOwner()->GetComponent<CollisionComponent>()->IsOverlapping(obj.get()))
		{
			if (obj->GetTag() == Tag::wall)
				m_Colliding = true;
			else if (obj->GetTag() == Tag::ladder)
			{
				++ladders;
				if (GetOwner()->GetComponent<CollisionComponent>()->IsUnder(obj.get()))
				{
					underLadder = true;
				}
			}
		}
	}
	if (ladders > 1)
		underLadder = false;

	if (m_Colliding || underLadder)
	{
		switch (m_State)
		{
		case CharacterState::idle:
			break;
		case CharacterState::left:
			pos.x += m_Speed * deltaTime;
			GetOwner()->GetTransform()->SetLocalPosition(pos.x, pos.y, pos.z);
			break;
		case CharacterState::right:
			pos.x -= m_Speed * deltaTime;
			GetOwner()->GetTransform()->SetLocalPosition(pos.x, pos.y, pos.z);
			break;
		case CharacterState::up:
			pos.y += m_LadderSpeed * deltaTime;
			GetOwner()->GetTransform()->SetLocalPosition(pos.x, pos.y, pos.z);
			break;
		case CharacterState::down:
			pos.y -= m_LadderSpeed * deltaTime;
			GetOwner()->GetTransform()->SetLocalPosition(pos.x, pos.y, pos.z);
			break;
		}
	}
}

void dae::PepperComponent::HandleAnim()
{
	switch (m_State)
	{
	case CharacterState::idle:
		m_Anim->SetClip(m_Idle);
		break;
	case CharacterState::left:
		if (m_OnPlatform)
			m_Anim->SetClip(m_RunLeft);
		break;
	case CharacterState::right:
		if (m_OnPlatform)
			m_Anim->SetClip(m_RunRight);
		break;
	case CharacterState::up:
		if (m_OnLadder)
			m_Anim->SetClip(m_Climb);
		break;
	case CharacterState::down:
		if (m_OnLadder)
			m_Anim->SetClip(m_ClimbDown);
		break;
	}
}
