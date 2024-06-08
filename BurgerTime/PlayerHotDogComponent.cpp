#include "PlayerHotDogComponent.h"

#include <iostream>

#include "CollisionComponent.h"
#include "GameObject.h"
#include "AnimationRenderComponent.h"
#include "EnemyComponent.h"
#include "PeterPepperComponent.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ServiceLocator.h"
#include "EnumClasses.h"
#include "../BurgerTime/LadderComponent.h"
#include "../BurgerTime/PlatformComponent.h"
#include "../BurgerTime/GameInstance.h"

namespace dae
{
	class PlatformComponent;
	class LadderComponent;
}

dae::PlayerHotDogComponent::PlayerHotDogComponent(GameObject* owner) :BaseComponent(owner)
{
	Initialize();
}


void dae::PlayerHotDogComponent::Update(float deltaTime)
{
	HandleMovement(deltaTime);
	HandleAnim(deltaTime);
	HandleStun(deltaTime);
	CheckPeter();
}

void dae::PlayerHotDogComponent::HandleStun(float deltaTime)
{
	if (m_State == PlayerHotDogState::stunned)
	{
		m_StunElapsed += deltaTime;
		if (m_StunElapsed > m_StunTime)
		{
			ResetState();
			m_StunElapsed = 0;
		}
	}
}

void dae::PlayerHotDogComponent::HandleMovement(float deltaTime)
{
	if (m_State != PlayerHotDogState::stunned && m_State != PlayerHotDogState::falling)
	{
		switch (m_State)
		{
		case PlayerHotDogState::idle:
			break;
		case PlayerHotDogState::left:
		{
			for (auto object : SceneManager::GetInstance().GetActiveScene().GetObjects())
			{
				auto colcomp = object->GetComponent<CollisionComponent>();
				if (colcomp)
				{
					if (m_CollisionComp->IsOverlapping(object.get()))
					{
						if (object->GetTag() == Tag::platform)
						{
							auto platcomp = object->GetComponent<PlatformComponent>();
							if (!platcomp->OnLeft(GetOwner()) && platcomp->InRange(GetOwner()))
							{
								auto pos = m_Transform->GetWorldPosition();
								pos.x -= m_MovementSpeed * deltaTime;
								pos.y = platcomp->GetFloorY();
								m_Transform->SetLocalPosition(pos);
								break;
							}

						}
					}
				}
			}

			break;
		}
		case PlayerHotDogState::right:
		{
			for (auto object : SceneManager::GetInstance().GetActiveScene().GetObjects())
			{
				auto colcomp = object->GetComponent<CollisionComponent>();
				if (colcomp)
				{
					if (m_CollisionComp->IsOverlapping(object.get()))
					{
						if (object->GetTag() == Tag::platform)
						{
							auto platcomp = object->GetComponent<PlatformComponent>();
							if (!platcomp->OnRight(GetOwner()) && platcomp->InRange(GetOwner()))
							{
								auto pos = m_Transform->GetWorldPosition();
								pos.x += m_MovementSpeed * deltaTime;
								pos.y = platcomp->GetFloorY();
								m_Transform->SetLocalPosition(pos);
								break;
							}

						}
					}
				}
			}
			break;
		}
		case PlayerHotDogState::down:
		{
			for (auto object : SceneManager::GetInstance().GetActiveScene().GetObjects())
			{
				auto colcomp = object->GetComponent<CollisionComponent>();
				if (colcomp)
				{
					if (m_CollisionComp->IsOverlapping(object.get()))
					{
						if (object->GetTag() == Tag::ladder)
						{
							auto laddercomp = object->GetComponent<LadderComponent>();
							if (!laddercomp->OnBottom(GetOwner()) && laddercomp->InRange(GetOwner()))
							{
								auto pos = m_Transform->GetWorldPosition();
								pos.y += m_MovementSpeed * deltaTime;
								pos.x = object->GetTransform()->GetWorldPosition().x;
								m_Transform->SetLocalPosition(pos);
								break;
							}
						}
					}
				}
			}
			break;
		}
		case PlayerHotDogState::up:
		{
			for (auto object : SceneManager::GetInstance().GetActiveScene().GetObjects())
			{
				auto colcomp = object->GetComponent<CollisionComponent>();
				if (colcomp)
				{
					if (m_CollisionComp->IsOverlapping(object.get()))
					{
						if (object->GetTag() == Tag::ladder)
						{
							auto laddercomp = object->GetComponent<LadderComponent>();
							if (!laddercomp->OnTop(GetOwner()) && laddercomp->InRange(GetOwner()))
							{
								auto pos = m_Transform->GetWorldPosition();
								pos.y -= m_MovementSpeed * deltaTime;
								pos.x = object->GetTransform()->GetWorldPosition().x;
								m_Transform->SetLocalPosition(pos);
								break;
							}
						}
					}
				}
			}
			break;
		}
		}
	}
}

void dae::PlayerHotDogComponent::InitAnimation(AnimationRenderComponent* comp)
{
	if (comp == nullptr)
		return;

	m_Anim = comp;

	m_RunLeft = m_Anim->AddClip(2, true);
	m_RunRight = m_Anim->AddClip(2, true);
	m_ClimbDown = m_Anim->AddClip(2, true);
	m_Climb = m_Anim->AddClip(2, true);
	m_Stunned = m_Anim->AddClip(2, false);
}

void dae::PlayerHotDogComponent::HandleAnim(float)
{
	switch (m_State)
	{
	case PlayerHotDogState::idle:
		m_Anim->SetClip(m_ClimbDown);
		break;
	case PlayerHotDogState::left:
		m_Anim->SetClip(m_RunLeft);
		break;
	case PlayerHotDogState::right:
		m_Anim->SetClip(m_RunRight);
		break;
	case PlayerHotDogState::up:
		m_Anim->SetClip(m_Climb);
		break;
	case PlayerHotDogState::down:
		m_Anim->SetClip(m_ClimbDown);
		break;
	case PlayerHotDogState::stunned:
		m_Anim->SetClip(m_Stunned);
		break;
	}
}

void dae::PlayerHotDogComponent::Stun()
{
	m_State = PlayerHotDogState::stunned;
}

void dae::PlayerHotDogComponent::CheckPeter()
{
	if (m_State != PlayerHotDogState::stunned && m_State != PlayerHotDogState::falling)
		for (auto object : SceneManager::GetInstance().GetActiveScene().GetObjects())
		{
			auto colcomp = object->GetComponent<CollisionComponent>();
			if (m_CollisionComp->IsOverlapping(object.get()))
			{
				if (colcomp)
					if (object->GetTag() == Tag::peter)
						object->GetComponent<PeterPepperComponent>()->Hit();
			}
		}
}

void dae::PlayerHotDogComponent::Initialize()
{
	m_Fall = dae::ServiceLocator::GetSoundSystem().AddSound("../Data/Sounds/enemyfall.wav");
	m_CollisionComp = GetOwner()->GetComponent<CollisionComponent>();
	m_Transform = GetOwner()->GetTransform();
}


void dae::PlayerHotDogComponent::SetState(PlayerHotDogState state)
{
	if (m_State != PlayerHotDogState::falling && m_State != PlayerHotDogState::stunned)
	{
		m_State = state;
		if (state == PlayerHotDogState::falling)
			ServiceLocator::GetSoundSystem().Play(m_Fall, 128);
	}

}

void dae::PlayerHotDogComponent::ResetState()
{
	m_State = PlayerHotDogState::idle;
	m_StunElapsed = 0;
}
