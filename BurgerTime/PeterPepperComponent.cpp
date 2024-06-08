#include "PeterPepperComponent.h"

#include "CollisionComponent.h"
#include "GameObject.h"
#include "AnimationRenderComponent.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "Scene.h"
#include "SceneManager.h"
#include "EnumClasses.h"
#include "../BurgerTime/LadderComponent.h"
#include "../BurgerTime/PlatformComponent.h"
#include "../BurgerTime/GameInstance.h"

dae::PeterPepperComponent::PeterPepperComponent(GameObject* owner) :BaseComponent(owner)
{
	m_Transform = owner->GetTransform();
	m_Collision = owner->GetComponent<CollisionComponent>();
}


void dae::PeterPepperComponent::Update(float deltaTime)
{
	if (m_Hit)
	{
		m_ElapsedInv += deltaTime;
		if (m_ElapsedInv > m_InvTime)
		{
			m_Hit = false;
			m_ElapsedInv = 0;
		}
	}
	HandleMovement(deltaTime);
	HandleAnim(deltaTime);
}

void dae::PeterPepperComponent::HandleMovement(float deltaTime)
{
	switch (m_State)
	{
	case CharacterState::idle:
		break;
	case CharacterState::left:
	{
		for (auto object : SceneManager::GetInstance().GetActiveScene().GetObjects())
		{
			auto colcomp = object->GetComponent<CollisionComponent>();
			if (colcomp)
			{
				if (m_Collision->IsOverlapping(object.get()))
				{
					if (object->GetTag() == Tag::platform)
					{
						auto platcomp = object->GetComponent<PlatformComponent>();
						if (!platcomp->OnLeft(GetOwner()) && platcomp->InRange(GetOwner()))
						{
							auto pos = m_Transform->GetWorldPosition();
							pos.x -= m_Speed * deltaTime;
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
	case CharacterState::right:
	{
		for (auto object : SceneManager::GetInstance().GetActiveScene().GetObjects())
		{
			auto colcomp = object->GetComponent<CollisionComponent>();
			if (colcomp)
			{
				if (m_Collision->IsOverlapping(object.get()))
				{
					if (object->GetTag() == Tag::platform)
					{
						auto platcomp = object->GetComponent<PlatformComponent>();
						if (!platcomp->OnRight(GetOwner()) && platcomp->InRange(GetOwner()))
						{
							auto pos = m_Transform->GetWorldPosition();
							pos.x += m_Speed * deltaTime;
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
	case CharacterState::down:
	{
		for (auto object : SceneManager::GetInstance().GetActiveScene().GetObjects())
		{
			auto colcomp = object->GetComponent<CollisionComponent>();
			if (colcomp)
			{
				if (m_Collision->IsOverlapping(object.get()))
				{
					if (object->GetTag() == Tag::ladder)
					{
						auto laddercomp = object->GetComponent<LadderComponent>();
						if (!laddercomp->OnBottom(GetOwner()) && laddercomp->InRange(GetOwner()))
						{
							auto pos = m_Transform->GetWorldPosition();
							pos.y += m_Speed * deltaTime;
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
	case CharacterState::up:
	{
		for (auto object : SceneManager::GetInstance().GetActiveScene().GetObjects())
		{
			auto colcomp = object->GetComponent<CollisionComponent>();
			if (colcomp)
			{
				if (m_Collision->IsOverlapping(object.get()))
				{
					if (object->GetTag() == Tag::ladder)
					{
						auto laddercomp = object->GetComponent<LadderComponent>();
						if (!laddercomp->OnTop(GetOwner()) && laddercomp->InRange(GetOwner()))
						{
							auto pos = m_Transform->GetWorldPosition();
							pos.y -= m_Speed * deltaTime;
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

void dae::PeterPepperComponent::InitAnimation(AnimationRenderComponent* comp)
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

void dae::PeterPepperComponent::HandleAnim(float)
{
	switch (m_State)
	{
	case CharacterState::idle:
		m_Anim->SetClip(m_Idle);
		break;
	case CharacterState::left:
		m_Anim->SetClip(m_RunLeft);
		break;
	case CharacterState::right:
		m_Anim->SetClip(m_RunRight);
		break;
	case CharacterState::up:
		m_Anim->SetClip(m_Climb);
		break;
	case CharacterState::down:
		m_Anim->SetClip(m_ClimbDown);
		break;
	}
}

void dae::PeterPepperComponent::AddPoints(GameObject* go)
{
	if (!m_SecondPlayer)
	{
		Tag tag = go->GetTag();

		switch (tag) {
		case Tag::hotdog:
			GetOwner()->GetComponent<ScoreComponent>()->AddPoints(100);
			break;
		case Tag::pickle:
			GetOwner()->GetComponent<ScoreComponent>()->AddPoints(200);
			break;
		case Tag::egg:
			GetOwner()->GetComponent<ScoreComponent>()->AddPoints(300);
			break;
		}
	}
	else
	{
		Tag tag = go->GetTag();

		switch (tag) {
		case Tag::hotdog:
			m_SecondPlayer->GetComponent<ScoreComponent>()->AddPoints(100);
			break;
		case Tag::pickle:
			m_SecondPlayer->GetComponent<ScoreComponent>()->AddPoints(200);
			break;
		case Tag::egg:
			m_SecondPlayer->GetComponent<ScoreComponent>()->AddPoints(300);
			break;
		}
	}
}

void dae::PeterPepperComponent::AddPoints(int amt)
{
	if (!m_SecondPlayer)
	{
		GetOwner()->GetComponent<ScoreComponent>()->AddPoints(amt);
	}
	else
	{
		m_SecondPlayer->GetComponent<ScoreComponent>()->AddPoints(amt);
	}
}

void dae::PeterPepperComponent::Hit()
{
	if (!m_Hit)
	{
		if (!m_SecondPlayer)
		{
			m_Hit = true;
			auto hp = GetOwner()->GetComponent<HealthComponent>();
			hp->Hit();
			if (hp->GetLives() == 0)
			{
				GameInstance::GetInstance().Died(GetOwner()->GetComponent<ScoreComponent>()->GetPoints());
			}
			else
			{
				GameInstance::GetInstance().Hit(hp->GetLives(), GetOwner()->GetComponent<ScoreComponent>()->GetPoints());
			}
		}
		else
		{
			m_Hit = true;
			auto hp = m_SecondPlayer->GetComponent<HealthComponent>();
			hp->Hit();
			if (hp->GetLives() == 0)
			{
				GameInstance::GetInstance().Died(m_SecondPlayer->GetComponent<ScoreComponent>()->GetPoints());
			}
			else
			{
				GameInstance::GetInstance().Hit(hp->GetLives(), m_SecondPlayer->GetComponent<ScoreComponent>()->GetPoints());
			}
		}

	}
}
