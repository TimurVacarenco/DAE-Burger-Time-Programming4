#include "EnemyComponent.h"
#include "GameObject.h"
#include "PlatformComponent.h"
#include <SceneManager.h>
#include "Scene.h"
#include "CollisionComponent.h"
#include "AnimationRenderComponent.h"
dae::EnemyComponent::EnemyComponent(GameObject* owner):
	BaseComponent(owner)
{
	Initialize();
}

void dae::EnemyComponent::Update(float deltaTime)
{
	HandleMovement(deltaTime);
	HandleCollision(deltaTime);
	HandleAnimation();
}

void dae::EnemyComponent::FixedUpdate(float deltaTime)
{
}

void dae::EnemyComponent::HandleMovement(float deltaTime)
{
	auto pos = GetOwner()->GetTransform()->GetLocalPosition();
	if (m_State != EnemyState::falling)
	{
		const auto& peterpos = m_Peter->GetTransform()->GetLocalPosition();


		m_OnPlatform = false;
		m_OnLadder = false;
		float ladderX{};
		float platformY{};

		PlatformComponent* platform = nullptr;
		std::vector<GameObject*> ladderObj{};

		for (auto& obj : SceneManager::GetInstance().GetActiveScene().GetObjects())
		{
			if (GetOwner()->GetComponent<CollisionComponent>()->IsOverlapping(obj.get()))
				if (obj->GetTag()==Tag::platform)
				{
					if (!GetOwner()->GetComponent<CollisionComponent>()->IsUnder(obj.get()))
					{
						m_OnPlatform = true;
						platform = obj->GetComponent<PlatformComponent>();
						platformY = platform->GetFloorPos().y + 92;
					}
				}
				else if (obj->GetTag()==Tag::ladder)
				{
					ladderObj.push_back(obj.get());
					if (!GetOwner()->GetComponent<CollisionComponent>()->IsUnder(obj.get()))
					{
						ladderX = obj->GetTransform()->GetLocalPosition().x + 16;
						if (abs(ladderX - GetOwner()->GetTransform()->GetLocalPosition().x) < 10.f)
						{
							m_OnLadder = true;
						}
					}


				}
		}
		if (m_OnLadder && !m_OnPlatform)
		{
			m_Direction.x = peterpos.x - pos.x;
			m_Switched = false;
			if (m_Direction.y > 0.f)
			{
				pos.y += m_ClimbSpeed * deltaTime;
				pos.x = ladderX;
				m_State = EnemyState::down;
			}
			else if (m_Direction.y < 0.f)
			{
				pos.y -= m_ClimbSpeed * deltaTime;
				pos.x = ladderX;
				m_State = EnemyState::up;
			}
		}
		else if (m_OnPlatform && !m_OnLadder)
		{
			m_Direction.y = peterpos.y - pos.y;
			m_Switched = false;
			if (m_Direction.x > 0.f)
			{
				pos.x += m_Speed * deltaTime;
				pos.y = platformY;
				m_State = EnemyState::right;

			}
			else if (m_Direction.x < 0.f)
			{
				pos.x -= m_Speed * deltaTime;
				pos.y = platformY;
				m_State = EnemyState::left;

			}
		}
		else if (m_OnLadder && m_OnPlatform)
		{
			if (!m_Switched) {
				m_Horizontal = false;
				if (ladderObj.size() == 1 && (pos.y > m_Bounds.x + m_Bounds.height && pos.y < m_Bounds.x + m_Bounds.width))
					m_Horizontal = ladderObj.at(0)->GetComponent<CollisionComponent>()->IsUnder(Rect{ pos.x,pos.y + m_ClimbSpeed * deltaTime ,48,48 });
				m_Switched = true;
			}

			if (!m_Horizontal)
			{
				if (m_Direction.y > 1.f)
				{
					pos.y += m_ClimbSpeed * deltaTime;
					pos.x = ladderX;
					m_State = EnemyState::down;
				}
				else if (m_Direction.y < -1.f)
				{
					pos.y -= m_ClimbSpeed * deltaTime;
					pos.x = ladderX;
					m_State = EnemyState::up;
				}
			}
			else
			{
				if (m_Direction.x > 0.f)
				{
					pos.x += m_Speed * deltaTime;
					pos.y = platformY;
					m_State = EnemyState::right;

				}
				else if (m_Direction.x < 0.f)
				{
					pos.x -= m_Speed * deltaTime;
					pos.y = platformY;
					m_State = EnemyState::left;

				}
			}
		}

		GetOwner()->GetTransform()->SetLocalPosition(pos.x, pos.y, 0);
	}
	else
	{
		pos.y += m_FallingSpeed* deltaTime;
		GetOwner()->GetTransform()->SetLocalPosition(pos.x, pos.y, pos.z);
	}
}

void dae::EnemyComponent::HandleCollision(float deltaTime)
{
	auto pos = GetOwner()->GetTransform()->GetLocalPosition();
	if (m_State != EnemyState::falling && m_State != EnemyState::dead)
	{
		bool underLadder = false;
		int ladders = 0;

		int platforms = 0;
		bool offPlatform = false;
		for (auto& obj : SceneManager::GetInstance().GetActiveScene().GetObjects())
		{
			if (GetOwner()->GetComponent<CollisionComponent>()->IsOverlapping(obj.get()))
			{
				if (obj->GetTag() == Tag::platform)
				{
					++platforms;
					if (GetOwner()->GetComponent<CollisionComponent>()->IsToSide(obj.get()))
					{
						offPlatform = true;
					}
				}
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

		if (platforms > 1)
		{
			offPlatform = false;
		}
		else if (offPlatform)
			m_Direction.x = -m_Direction.x;

		if (offPlatform || underLadder)
		{
			switch (m_State)
			{
			case EnemyState::left:
				pos.x += m_Speed * deltaTime;
				break;
			case EnemyState::right:
				pos.x -= m_Speed * deltaTime;
				break;
			case EnemyState::up:
				pos.y += m_ClimbSpeed * deltaTime;
				break;
			case EnemyState::down:
				pos.y -= m_ClimbSpeed * deltaTime;
				break;
			}
			GetOwner()->GetTransform()->SetLocalPosition(pos.x, pos.y, pos.z);
		}
	}
}

void dae::EnemyComponent::SetState(EnemyState state)
{
	m_State = state;
	if (m_State == EnemyState::falling)
	{
		auto& pos = GetOwner()->GetTransform()->GetLocalPosition();
		GetOwner()->GetTransform()->SetLocalPosition(pos.x, pos.y + 3, pos.z);
	}
}

void dae::EnemyComponent::InitAnimation(AnimationRenderComponent* animComp, std::string textureLoc)
{
	if (animComp == nullptr)
		return;
	animComp->SetTexture(textureLoc);

	m_Anim = animComp;

	m_RunLeft = m_Anim->AddClip(2, true);
	m_RunRight = m_Anim->AddClip(2, true);
	m_ClimbDown = m_Anim->AddClip(2, true);
	m_Climb = m_Anim->AddClip(2, true);
	m_Stunned = m_Anim->AddClip(2, false);
}

void dae::EnemyComponent::HandleAnimation() const
{
	switch (m_State)
	{
	case EnemyState::left:
		m_Anim->SetClip(m_RunLeft);
		return;
	case EnemyState::right:
		m_Anim->SetClip(m_RunRight);
		return;
	case EnemyState::down:
		m_Anim->SetClip(m_ClimbDown);
		return;
	case EnemyState::up:
		m_Anim->SetClip(m_Climb);
		return;
	case EnemyState::stunned:
		m_Anim->SetClip(m_Stunned);
		return;
	}
}

void dae::EnemyComponent::SetPeter(GameObject* peterObj)
{
	if (!peterObj)
		return;
	m_Peter = peterObj;
	auto& pos = GetOwner()->GetTransform()->GetLocalPosition();
	auto& peterpos = m_Peter->GetTransform()->GetLocalPosition();

	m_Direction.x = peterpos.x - pos.x;
	m_Direction.y = peterpos.y - pos.y;
}

void dae::EnemyComponent::Initialize()
{
	m_Bounds = SceneManager::GetInstance().GetActiveScene().GetBounds();
}