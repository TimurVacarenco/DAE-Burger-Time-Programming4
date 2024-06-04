#pragma once
#include <memory>
#include "GameObject.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "../BurgerTime/PepperComponent.h" 

namespace dae
{
	//class PepperComponent;
	class BaseCommand
	{
	public:
		BaseCommand(std::shared_ptr<GameObject> obj):m_pActor{ obj } {}
		virtual void SetActor(std::shared_ptr<GameObject> pGameObject) { m_pActor = pGameObject; };
		virtual ~BaseCommand() = default;
		virtual void Execute() = 0;
		const std::shared_ptr<GameObject> GetActor() { return m_pActor; }
	private:
		std::shared_ptr<GameObject> m_pActor;
	};


	class KillCommand : public BaseCommand
	{
	public:
		KillCommand(std::shared_ptr<GameObject> obj) :BaseCommand(obj) {}
		void Execute() override { GetActor()->GetComponent<HealthComponent>()->Kill(); }
	};

	class AddPointsCommand : public BaseCommand
	{
	public:
		AddPointsCommand(std::shared_ptr<GameObject> obj) :BaseCommand(obj) {}
		void Execute() override { GetActor()->GetComponent<ScoreComponent>()->AddPoints(100); }
	};

	class MoveLeft :public BaseCommand
	{
	public:
		MoveLeft(std::shared_ptr<GameObject> obj) : BaseCommand(obj) {}
		void Execute() override
		{
			GetActor()->GetComponent<PepperComponent>()->SetState(CharacterState::left);
		}
	};

	class MoveRight :public BaseCommand
	{
	public:
		MoveRight(std::shared_ptr<GameObject> obj) : BaseCommand(obj) {}
		void Execute() override
		{
			GetActor()->GetComponent<PepperComponent>()->SetState(CharacterState::right);
		}
	};

	class MoveUp :public BaseCommand
	{
	public:
		MoveUp(std::shared_ptr<GameObject> obj) : BaseCommand(obj) {}
		void Execute() override
		{
			GetActor()->GetComponent<PepperComponent>()->SetState(CharacterState::up);
		}
	};

	class MoveDown :public BaseCommand
	{
	public:
		MoveDown(std::shared_ptr<GameObject> obj) : BaseCommand(obj) {}
		void Execute() override
		{
			GetActor()->GetComponent<PepperComponent>()->SetState(CharacterState::down);
		}
	};

	class Idle :public BaseCommand
	{
	public:
		Idle(std::shared_ptr<GameObject> obj) : BaseCommand(obj) {}
		void Execute() override
		{
			GetActor()->GetComponent<PepperComponent>()->SetState(CharacterState::idle);
		}
	};

}