#include "EnemyComponent.h"
#include "GameObject.h"
#include "PlatformComponent.h"
#include <SceneManager.h>
#include "Scene.h"
#include "CollisionComponent.h"
#include "AnimationRenderComponent.h"
#include <ServiceLocator.h>
#include "PepperComponent.h"
#include "PeterPepperComponent.h"
#include "LadderComponent.h"


dae::EnemyComponent::EnemyComponent(GameObject* owner):
	BaseComponent(owner)
{
	Initialize();
}

void dae::EnemyComponent::Update(float deltaTime)
{
	HandleMovement(deltaTime);
	HandleAnimation();
	HandleStun(deltaTime);
}

void dae::EnemyComponent::HandleMovement(float deltaTime)
{
	if (m_State != EnemyState::falling && m_State != EnemyState::stunned)
	{
		CalculateDirection();
		if (m_MovementDirection.x == 0 && m_MovementDirection.y == 0)
		{
			m_MovementDirection = m_Direction;
		}
		GameObject* platform = nullptr;
		GameObject* ladder = nullptr;
		Vector3 pos = GetOwner()->GetTransform()->GetWorldPosition();

		float platformDistance = FLT_MAX;
		float ladderDistance = FLT_MAX;
		for (auto& object : SceneManager::GetInstance().GetActiveScene().GetObjects())
		{
			if (object->GetComponent<CollisionComponent>())
			{
				if (m_Collision->IsOverlapping(object.get()))
				{
					switch (object->GetTag())
					{
					case Tag::peter:
					case Tag::peterjr:
						object->GetComponent<PeterPepperComponent>()->Hit();
						break;

					case Tag::ladder:
					{
						auto laddercomp = object->GetComponent<LadderComponent>();
						if (laddercomp->InRange(GetOwner()))
						{
							if (m_MovementDirection.y > 0)
							{
								if (!laddercomp->OnBottom(GetOwner()))
								{
									if (std::abs(object->GetTransform()->GetWorldPosition().y - GetOwner()->GetTransform()->GetWorldPosition().y) < ladderDistance)
									{
										ladderDistance = std::abs(object->GetTransform()->GetWorldPosition().y - GetOwner()->GetTransform()->GetWorldPosition().y);
										ladder = object.get();
									}
								}
								else
								{
									m_DirectionChanged = false;
									m_MovementDirection = m_Direction;
								}
							}

							if (m_MovementDirection.y < 0)
							{
								if (!laddercomp->OnTop(GetOwner()))
								{
									if (std::abs(object->GetTransform()->GetWorldPosition().y - GetOwner()->GetTransform()->GetWorldPosition().y) < ladderDistance)
									{
										ladderDistance = std::abs(object->GetTransform()->GetWorldPosition().y - GetOwner()->GetTransform()->GetWorldPosition().y);
										ladder = object.get();
									}
								}
								else
								{
									m_DirectionChanged = false;
									m_MovementDirection = m_Direction;
								}
							}
						}
						break;
					}

					case Tag::platform:
					{
						auto platcomp = object->GetComponent<PlatformComponent>();
						if (platcomp->InRange(GetOwner()))
						{
							if (m_MovementDirection.x < 0)
							{
								if (!platcomp->OnLeft(GetOwner()))
								{
									if (std::abs(object->GetTransform()->GetWorldPosition().x - GetOwner()->GetTransform()->GetWorldPosition().x) < platformDistance)
									{
										platformDistance = std::abs(object->GetTransform()->GetWorldPosition().x - GetOwner()->GetTransform()->GetWorldPosition().x);
										platform = object.get();
									}
								}
								else
								{
									m_DirectionChanged = true;
									m_MovementDirection.x = -m_MovementDirection.x;
									m_MovementDirection.y = m_Direction.y;
								}
							}

							if (m_MovementDirection.x > 0)
							{
								if (!platcomp->OnRight(GetOwner()))
								{
									if (std::abs(object->GetTransform()->GetWorldPosition().x - GetOwner()->GetTransform()->GetWorldPosition().x) < platformDistance)
									{
										platformDistance = std::abs(object->GetTransform()->GetWorldPosition().x - GetOwner()->GetTransform()->GetWorldPosition().x);
										platform = object.get();
									}
								}
								else
								{
									m_DirectionChanged = true;
									m_MovementDirection.x = -m_MovementDirection.x;
									m_MovementDirection.y = m_Direction.y;
								}
							}
						}
						break;
					}
					}
				}
			}
		}

		if (platform && ladder)
		{
			if (m_DirectionChanged)
			{
				if (m_MovementDirection.y > 0)
				{
					pos.y += m_ClimbSpeed * deltaTime;
					m_State = EnemyState::down;
					pos.x = ladder->GetTransform()->GetWorldPosition().x;
					m_Transform->SetLocalPosition(pos);
				}
				else if (m_MovementDirection.y < 0)
				{
					pos.y -= m_ClimbSpeed * deltaTime;
					m_State = EnemyState::up;
					pos.x = ladder->GetTransform()->GetWorldPosition().x;
					m_Transform->SetLocalPosition(pos);
				}
				else if (ladder->GetComponent<LadderComponent>()->OnTop(GetOwner()))
				{
					pos.y += m_ClimbSpeed * deltaTime;
					m_State = EnemyState::down;
					pos.x = ladder->GetTransform()->GetWorldPosition().x;
					m_Transform->SetLocalPosition(pos);
				}
				else
				{
					pos.y -= m_ClimbSpeed * deltaTime;
					m_State = EnemyState::up;
					pos.x = ladder->GetTransform()->GetWorldPosition().x;
					m_Transform->SetLocalPosition(pos);
				}

			}
			else
			{
				if (abs(m_MovementDirection.x) > abs(m_MovementDirection.y))
				{
					if (m_MovementDirection.x < 0)
					{
						pos.x -= m_Speed * deltaTime;
						m_State = EnemyState::left;
						pos.y = platform->GetComponent<PlatformComponent>()->GetFloorY();
						m_Transform->SetLocalPosition(pos);
					}
					if (m_MovementDirection.x > 0)
					{
						pos.x += m_Speed * deltaTime;
						m_State = EnemyState::right;
						pos.y = platform->GetComponent<PlatformComponent>()->GetFloorY();
						m_Transform->SetLocalPosition(pos);
					}
				}
				else
				{
					if (m_MovementDirection.y > 0)
					{
						pos.y += m_ClimbSpeed * deltaTime;
						m_State = EnemyState::down;
						pos.x = ladder->GetTransform()->GetWorldPosition().x;
						m_Transform->SetLocalPosition(pos);
					}
					if (m_MovementDirection.y < 0)
					{
						pos.y -= m_ClimbSpeed * deltaTime;
						m_State = EnemyState::up;
						pos.x = ladder->GetTransform()->GetWorldPosition().x;
						m_Transform->SetLocalPosition(pos);
					}
				}
			}

		}
		else if (ladder)
		{
			if (m_MovementDirection.y > 0)
			{
				pos.y += m_ClimbSpeed * deltaTime;
				m_State = EnemyState::down;
				pos.x = ladder->GetTransform()->GetWorldPosition().x;
				m_Transform->SetLocalPosition(pos);
			}
			if (m_MovementDirection.y < 0)
			{
				pos.y -= m_ClimbSpeed * deltaTime;
				m_State = EnemyState::up;
				pos.x = ladder->GetTransform()->GetWorldPosition().x;
				m_Transform->SetLocalPosition(pos);
			}
		}
		else if (platform)
		{
			if (m_MovementDirection.x < 0)
			{
				pos.x -= m_Speed * deltaTime;
				m_State = EnemyState::left;
				pos.y = platform->GetComponent<PlatformComponent>()->GetFloorY();
				m_Transform->SetLocalPosition(pos);
			}
			if (m_MovementDirection.x > 0)
			{
				pos.x += m_Speed * deltaTime;
				m_State = EnemyState::right;
				pos.y = platform->GetComponent<PlatformComponent>()->GetFloorY();
				m_Transform->SetLocalPosition(pos);
			}
		}
	}
}

void dae::EnemyComponent::SetState(EnemyState state)
{
	CalculateDirection();
	m_State = state;
	if (state == EnemyState::falling)
	{
		ServiceLocator::GetSoundSystem().Play(m_Fall, 128);
	}
}
void dae::EnemyComponent::InitAnimation(AnimationRenderComponent* animComp, std::string textureLoc)
{
	if (animComp == nullptr) return;

	animComp->SetTexture(textureLoc);
	
	m_Anim = animComp;
	m_RunLeft = m_Anim->AddClip(2, true);
	m_RunRight = m_Anim->AddClip(2, true);
	m_ClimbDown = m_Anim->AddClip(2, true);
	m_Climb = m_Anim->AddClip(2, true);
	m_Stunned = m_Anim->AddClip(2, false);
}

void dae::EnemyComponent::Kill()
{
	ServiceLocator::GetSoundSystem().Play(m_Hit, 100);
	m_State = EnemyState::dead;
	SceneManager::GetInstance().GetActiveScene().Remove(GetOwner());
}

void dae::EnemyComponent::Stun()
{
	m_State = EnemyState::stunned;
}

void dae::EnemyComponent::CalculateDirection()
{
	Vector3 peterPos = m_Peter->GetTransform()->GetWorldPosition();
	Vector3 pos = GetOwner()->GetTransform()->GetWorldPosition();
	m_Direction.y = peterPos.y - pos.y;
	m_Direction.x = peterPos.x - pos.x;
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

void dae::EnemyComponent::HandleStun(float deltaTime)
{
	if (m_State == EnemyState::stunned)
	{
		m_StunElapsed += deltaTime;
		if (m_StunElapsed > m_StunTime)
		{
			m_State = EnemyState::left;
			m_StunElapsed = 0;
		}
	}
}

void dae::EnemyComponent::SetPeter(GameObject* peterObj)
{
	if (!peterObj)
		return;
	m_Peter = peterObj;
	auto& pos = GetOwner()->GetTransform()->GetWorldPosition();
	auto& peterpos = m_Peter->GetTransform()->GetWorldPosition();

	m_Direction.x = peterpos.x - pos.x;
	m_Direction.y = peterpos.y - pos.y;
}

void dae::EnemyComponent::Initialize()
{
	m_Hit = dae::ServiceLocator::GetSoundSystem().AddSound("../Data/Sounds/enemyhit.wav");
	m_Fall = dae::ServiceLocator::GetSoundSystem().AddSound("../Data/Sounds/enemyfall.wav");
	m_Collision = GetOwner()->GetComponent<CollisionComponent>();
	m_Transform = GetOwner()->GetTransform();
}