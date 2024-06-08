#include "PepperComponent.h"

#include "CollisionComponent.h"
#include "EnemyComponent.h"
#include "GameObject.h"
#include "PeterPepperComponent.h"
#include "PlayerHotDogComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ServiceLocator.h"

dae::PepperComponent::PepperComponent(GameObject* owner)
	:BaseComponent(owner),
	m_Peter(owner)
{
	Initialize();
}

void dae::PepperComponent::Initialize()
{
	m_RenderComp = GetOwner()->AddComponent<RenderComponent>();
	m_RenderComp->SetEnabled(false);
	m_RenderComp->SetTexture("../Data/Sprites/PeterPepper/pepper.png");
	m_RenderComp->SetDimensions(32, 32);

	m_Sound = dae::ServiceLocator::GetSoundSystem().AddSound("../Data/Sounds/pepper.wav");
}

void dae::PepperComponent::Activate()
{
	if (!m_Active && m_Amt > 0)
	{
		m_Active = true;
		auto pp = m_Peter->GetComponent<PeterPepperComponent>();
		auto& pos = m_Peter->GetTransform()->GetWorldPosition();

		switch (pp->GetState())
		{
		case CharacterState::left:
		{
			m_Peter->GetTransform()->GetWorldPosition();
			m_RenderComp->SetOffsetX(-32);
			m_RenderComp->SetOffsetY(0);
			m_RenderComp->SetEnabled(true);
			for (auto& obj : SceneManager::GetInstance().GetActiveScene().GetObjects())
			{
				Rect rect{ pos.x - 32,pos.y,32,32 };
				if (auto enemy = obj->GetComponent<EnemyComponent>())
					if (obj->GetComponent<CollisionComponent>()->IsOverlapping(rect))
					{
						enemy->Stun();
					}
				if (auto playerdog = obj->GetComponent<PlayerHotDogComponent>())
					if (obj->GetComponent<CollisionComponent>()->IsOverlapping(rect))
					{
						playerdog->Stun();
					}
			}
			--m_Amt;
			Notify(GetOwner(), Event::ON_PEPPER);
			dae::ServiceLocator::GetSoundSystem().Play(m_Sound, 100);
			break;
		}
		case CharacterState::right:
		{
			m_Peter->GetTransform()->GetWorldPosition();
			m_RenderComp->SetOffsetY(0);
			m_RenderComp->SetOffsetX(32);
			m_RenderComp->SetEnabled(true);
			for (auto& obj : SceneManager::GetInstance().GetActiveScene().GetObjects())
			{
				Rect rect{ pos.x + 32,pos.y,32,32 };
				if (auto enemy = obj->GetComponent<EnemyComponent>())
					if (obj->GetComponent<CollisionComponent>()->IsOverlapping(rect))
					{
						enemy->Stun();
					}
				if (auto playerdog = obj->GetComponent<PlayerHotDogComponent>())
					if (obj->GetComponent<CollisionComponent>()->IsOverlapping(rect))
					{
						playerdog->Stun();
					}
			}
			--m_Amt;
			Notify(GetOwner(), Event::ON_PEPPER);
			dae::ServiceLocator::GetSoundSystem().Play(m_Sound, 100);
			break;
		}
		case CharacterState::up:
		{
			m_Peter->GetTransform()->GetWorldPosition();
			m_RenderComp->SetOffsetY(-32);
			m_RenderComp->SetOffsetX(0);
			m_RenderComp->SetEnabled(true);
			for (auto& obj : SceneManager::GetInstance().GetActiveScene().GetObjects())
			{
				Rect rect{ pos.x ,pos.y - 32,32,32 };
				if (auto enemy = obj->GetComponent<EnemyComponent>())
					if (obj->GetComponent<CollisionComponent>()->IsOverlapping(rect))
					{
						enemy->Stun();
					}
				if (auto playerdog = obj->GetComponent<PlayerHotDogComponent>())
					if (obj->GetComponent<CollisionComponent>()->IsOverlapping(rect))
					{
						playerdog->Stun();
					}

			}
			--m_Amt;
			Notify(GetOwner(), Event::ON_PEPPER);
			dae::ServiceLocator::GetSoundSystem().Play(m_Sound, 100);
			break;
		}

		case CharacterState::down:
		{
			m_Peter->GetTransform()->GetWorldPosition();
			m_RenderComp->SetOffsetY(32);
			m_RenderComp->SetOffsetX(0);
			m_RenderComp->SetEnabled(true);
			for (auto& obj : SceneManager::GetInstance().GetActiveScene().GetObjects())
			{
				Rect rect{ pos.x,pos.y + 32,32,32 };
				if (auto enemy = obj->GetComponent<EnemyComponent>())
					if (obj->GetComponent<CollisionComponent>()->IsOverlapping(rect))
					{
						enemy->Stun();
					}
				if (auto playerdog = obj->GetComponent<PlayerHotDogComponent>())
					if (obj->GetComponent<CollisionComponent>()->IsOverlapping(rect))
					{
						playerdog->Stun();
					}
			}
			--m_Amt;
			Notify(GetOwner(), Event::ON_PEPPER);
			dae::ServiceLocator::GetSoundSystem().Play(m_Sound, 100);
			break;
		}
		default:
		{
			m_Active = false;
			break;
		}
		}
	}

}

void dae::PepperComponent::Update(float deltaTime)
{
	if (m_Active)
	{
		m_ElapsedTime += deltaTime;
		if (m_ElapsedTime > m_TimeToShow)
		{
			m_Active = false;
			m_RenderComp->SetEnabled(false);
			m_ElapsedTime = 0;
		}
	}
}
