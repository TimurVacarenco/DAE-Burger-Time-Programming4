#pragma once
#include <memory>
#include "GameObject.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "../BurgerTime/PeterPepperComponent.h" 
#include "../BurgerTime/PeterPepper.h"
#include "../BurgerTime/MenuComponent.h"
#include "../BurgerTime/PlayerHotDogComponent.h"
#include "../BurgerTime/PepperComponent.h"
#include "../BurgerTime/GameInstance.h"
namespace dae
{
	class MenuComponent;
	class BaseCommand
	{
	public:
		BaseCommand(std::shared_ptr<GameObject> obj):m_pActor{ obj } {}
		virtual ~BaseCommand() = default;
		virtual void Execute() = 0;
		const std::shared_ptr<GameObject> GetActor() { return m_pActor; }
	private:
		std::shared_ptr<GameObject> m_pActor;
	};

#pragma region TestCommands
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
#pragma endregion
#pragma region PeterPepper
	class MoveLeft :public BaseCommand
	{
	public:
		MoveLeft(std::shared_ptr<GameObject> obj) : BaseCommand(obj) {}
		void Execute() override
		{
			GetActor()->GetComponent<PeterPepperComponent>()->SetState(CharacterState::left);
		}
	};

	class MoveRight :public BaseCommand
	{
	public:
		MoveRight(std::shared_ptr<GameObject> obj) : BaseCommand(obj) {}
		void Execute() override
		{
			GetActor()->GetComponent<PeterPepperComponent>()->SetState(CharacterState::right);
		}
	};

	class MoveUp :public BaseCommand
	{
	public:
		MoveUp(std::shared_ptr<GameObject> obj) : BaseCommand(obj) {}
		void Execute() override
		{
			GetActor()->GetComponent<PeterPepperComponent>()->SetState(CharacterState::up);
		}
	};

	class MoveDown :public BaseCommand
	{
	public:
		MoveDown(std::shared_ptr<GameObject> obj) : BaseCommand(obj) {}
		void Execute() override
		{
			GetActor()->GetComponent<PeterPepperComponent>()->SetState(CharacterState::down);
		}
	};

	class Idle :public BaseCommand
	{
	public:
		Idle(std::shared_ptr<GameObject> obj) : BaseCommand(obj) {}
		void Execute() override
		{
			GetActor()->GetComponent<PeterPepperComponent>()->SetState(CharacterState::idle);
		}
	};

	class Pepper : public BaseCommand
	{
	public:
		Pepper(std::shared_ptr<GameObject> obj) : BaseCommand(obj) {}
		void Execute() override 
		{
			GetActor()->GetComponent<PepperComponent>()->Activate(); 
		}
	};

#pragma endregion
#pragma region Menu
	class MenuNext : public BaseCommand
	{
	public:
		MenuNext(std::shared_ptr<GameObject> obj) : BaseCommand(obj) {}
		void Execute() override { GetActor()->GetComponent<MenuComponent>()->NextSelection(); }
	};

	class MenuPrevious : public BaseCommand
	{
	public:
		MenuPrevious(std::shared_ptr<GameObject> obj) : BaseCommand(obj) {}
		void Execute() override { GetActor()->GetComponent<MenuComponent>()->PreviousSelection(); }
	};

	class MenuStart : public BaseCommand
	{
	public:
		MenuStart(std::shared_ptr<GameObject> obj) : BaseCommand(obj) {}
		void Execute() override { GetActor()->GetComponent<MenuComponent>()->Start(); }
	};
#pragma endregion
#pragma region HotDogPlayer
	class HotDogIdle : public BaseCommand
	{
	public:
		HotDogIdle(std::shared_ptr<GameObject> obj) : BaseCommand(obj) {}
		void Execute() override { GetActor()->GetComponent<PlayerHotDogComponent>()->SetState(PlayerHotDogState::idle); }
	};

	class HotDogMoveLeft : public BaseCommand
	{
	public:
		HotDogMoveLeft(std::shared_ptr<GameObject> obj) : BaseCommand(obj) {}
		void Execute() override { GetActor()->GetComponent<PlayerHotDogComponent>()->SetState(PlayerHotDogState::left); }
	};

	class HotDogMoveRight : public BaseCommand
	{
	public:
		HotDogMoveRight(std::shared_ptr<GameObject> obj) : BaseCommand(obj) {}
		void Execute() override { GetActor()->GetComponent<PlayerHotDogComponent>()->SetState(PlayerHotDogState::right); }
	};

	class HotDogMoveUp : public BaseCommand
	{
	public:
		HotDogMoveUp(std::shared_ptr<GameObject> obj) : BaseCommand(obj) {}
		void Execute() override { GetActor()->GetComponent<PlayerHotDogComponent>()->SetState(PlayerHotDogState::up); }
	};

	class HotDogMoveDown : public BaseCommand
	{
	public:
		HotDogMoveDown(std::shared_ptr<GameObject> obj) : BaseCommand(obj) {}
		void Execute() override { GetActor()->GetComponent<PlayerHotDogComponent>()->SetState(PlayerHotDogState::down); }
	};
#pragma endregion
}