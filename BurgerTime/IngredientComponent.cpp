#include "IngredientComponent.h"

#include <iostream>

#include "CollisionComponent.h"
#include "EnemyComponent.h"
#include "GameInstance.h"
#include "GameObject.h"
#include "PeterPepperComponent.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ServiceLocator.h"
#include "PlatformComponent.h"
#include "PlayerHotDogComponent.h"

dae::IngredientComponent::IngredientComponent(GameObject* owner)
	:BaseComponent(owner)
{
	Initialize();
}

void dae::IngredientComponent::Update(float deltaTime)
{
	if (!m_Peter)
	{
		for (auto& obj : SceneManager::GetInstance().GetActiveScene().GetObjects())
		{
			if (obj->GetTag() == Tag::peter)
			{
				m_Peter = obj.get();
				break;
			}
		}
	}
	HandleMovement(deltaTime);
	HandleCollision(deltaTime);
}

void dae::IngredientComponent::HandleMovement(float deltaTime)
{
	if (m_State == IngredientState::falling)
	{
		auto pos = GetOwner()->GetTransform()->GetWorldPosition();
		pos.y += m_FallSpeed * deltaTime;
		GetOwner()->GetTransform()->SetLocalPosition(pos.x, pos.y, pos.z);
	}

}

void dae::IngredientComponent::HandleCollision(float)
{
	switch (m_State)
	{
	case IngredientState::idle:
	{
		int amtDropped{};
		for (int i{}; i < 4; ++i)
		{
			if (m_DropStates[i] == true)
				++amtDropped;
		}
		for (auto& obj : SceneManager::GetInstance().GetActiveScene().GetObjects())
		{
			for (int i{}; i < (int)m_Collisions.size(); ++i)
			{
				if (m_Collisions[i]->IsOverlapping(obj.get()))
				{
					if (obj->GetTag() == Tag::peter || obj->GetTag() == Tag::peterjr)
					{
						m_DropStates[i] = true;
						m_Sprites[i]->SetOffsetY(5);

					}
					if (i == 0 && obj.get() != m_Platform && obj->GetTag() == Tag::platform)
					{
						m_Platform = obj.get();
					}
					if (obj->GetComponent<EnemyComponent>())
					{
						if (std::find(m_Enemies.begin(), m_Enemies.end(), obj.get()) == m_Enemies.end())
							m_Enemies.push_back(obj.get());
					}
					if (obj->GetTag() == Tag::playerhotdog)
					{
						m_PlayerHotDog = obj.get();
					}
				}
			}
		}

		int after{};
		for (int i{}; i < 4; ++i)
		{
			if (m_DropStates[i] == true)
				++after;
		}
		if (after > amtDropped)
			ServiceLocator::GetSoundSystem().Play(m_Walk, 100);

		bool dropped = true;
		for (int i{}; i < 4; ++i)
		{
			if (m_DropStates[i] == false)
			{
				dropped = false;
				break;
			}
		}

		if (dropped)
		{
			m_State = IngredientState::falling;
			auto pos = GetOwner()->GetTransform()->GetWorldPosition();
			pos.y += 8;
			GetOwner()->GetTransform()->SetLocalPosition(pos.x, pos.y, pos.z);
			for (auto enemy : m_Enemies)
			{
				enemy->GetComponent<EnemyComponent>()->SetState(EnemyState::falling);
				enemy->SetParent(GetOwner(), true);
			}
			if (m_PlayerHotDog)
			{
				m_PlayerHotDog->GetComponent<PlayerHotDogComponent>()->SetState(PlayerHotDogState::falling);
				m_PlayerHotDog->SetParent(GetOwner(), true);
			}
			m_LevelsToFall = (int)m_Enemies.size();
			if (m_PlayerHotDog)
				++m_LevelsToFall;

			switch (m_LevelsToFall)
			{
			case 1:
				m_Peter->GetComponent<PeterPepperComponent>()->AddPoints(500);
				break;
			case 2:
				m_Peter->GetComponent<PeterPepperComponent>()->AddPoints(1000);
				break;
			case 3:
				m_Peter->GetComponent<PeterPepperComponent>()->AddPoints(2000);
				break;
			case 4:
				m_Peter->GetComponent<PeterPepperComponent>()->AddPoints(4000);
				break;
			case 5:
				m_Peter->GetComponent<PeterPepperComponent>()->AddPoints(8000);
				break;
			default:
				if (m_LevelsToFall >= 6)
					m_Peter->GetComponent<PeterPepperComponent>()->AddPoints(16000);
				break;
			}

		}
		else
		{
			m_Enemies.clear();
			m_PlayerHotDog = nullptr;
		}
		break;
	}
	case IngredientState::falling:
	{
		for (auto& obj : SceneManager::GetInstance().GetActiveScene().GetObjects())
		{
			for (int i{}; i < (int)m_Collisions.size(); ++i)
			{
				if (m_Collisions[i]->IsOverlapping(obj.get()))
				{
					if (i == 0)
					{
						if (obj.get() == m_Platform)
							break;
						if (obj->GetTag() == Tag::platform && obj.get() != m_Platform)
						{
							if (obj->GetComponent<PlatformComponent>()->OnBottom(GetOwner()))
							{
								if (m_LevelsToFall == 0)
								{
									m_State = IngredientState::idle;
									m_Platform = obj.get();
									for (int j{}; j < 4; ++j)
									{
										m_DropStates[j] = false;
										m_Sprites[j]->SetOffsetY(0);
									}

									for (auto enemy : m_Enemies)
									{
										enemy->GetComponent<EnemyComponent>()->SetState(EnemyState::left);
										enemy->SetParent(nullptr);
									}
									if (m_PlayerHotDog)
									{
										m_PlayerHotDog->GetComponent<PlayerHotDogComponent>()->ResetState();
										m_PlayerHotDog->SetParent(nullptr);
										m_PlayerHotDog = nullptr;
									}
									m_Peter->GetComponent<PeterPepperComponent>()->AddPoints(50);
									ServiceLocator::GetSoundSystem().Play(m_Bounce, 100);
								}
								else
								{
									m_Platform = obj.get();
									--m_LevelsToFall;
									m_Peter->GetComponent<PeterPepperComponent>()->AddPoints(50);
								}
							}
						}
						else if (auto comp = obj->GetComponent<IngredientComponent>())
						{
							if (comp->m_State == IngredientState::plated)
							{
								m_State = IngredientState::plated;

								if (GetOwner()->GetTag() == Tag::topbun)
									GameInstance::GetInstance().FillPlate();
								ServiceLocator::GetSoundSystem().Play(m_Bounce, 100);
							}
							else {
								m_CollidedIngredient = obj.get();
								comp->SetState(IngredientState::falling);
							}
						}
						else if (obj->GetTag() == Tag::plate)
						{
							for (int j{}; j < 4; ++j)
							{
								m_DropStates[j] = false;
								m_Sprites[j]->SetOffsetY(0);
							}
							m_State = IngredientState::plated;
							m_Enemies.clear();
							ServiceLocator::GetSoundSystem().Play(m_Bounce, 100);
							m_Peter->GetComponent<PeterPepperComponent>()->AddPoints(50);
						}
					}

					if (auto comp = obj->GetComponent<EnemyComponent>())
					{
						if (comp->GetState() != EnemyState::falling)
							comp->Kill();

					}
				}


			}


		}
	}
	}
}

void dae::IngredientComponent::SetCollisions(std::vector<CollisionComponent*>& cols)
{
	m_Collisions = cols;
}

void dae::IngredientComponent::SetSprites(std::vector<RenderComponent*>& sprites)
{
	m_Sprites = sprites;
}

void dae::IngredientComponent::SetState(IngredientState state)
{
	if (m_State != IngredientState::plated)
	{
		m_State = state;
		if (m_State == IngredientState::falling)
		{
			for (auto& obj : SceneManager::GetInstance().GetActiveScene().GetObjects())
			{
				if (m_Collisions[1]->IsOverlapping(obj.get()))
				{
					if (obj->GetTag() == Tag::platform)
					{
						m_Platform = obj.get();
					}
				}
			}
			for (int i{}; i < 4; ++i)
			{
				m_DropStates[i] = false;
				m_Sprites[i]->SetOffsetY(0);
			}
		}
	}
}

void dae::IngredientComponent::Initialize()
{
	m_Walk = dae::ServiceLocator::GetSoundSystem().AddSound("../Data/Sounds/ingredientwalk.wav");
	m_Bounce = dae::ServiceLocator::GetSoundSystem().AddSound("../Data/Sounds/bounce.wav");
}
