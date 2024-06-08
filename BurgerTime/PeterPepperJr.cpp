#include "PeterPepperJr.h"

#include "AnimationRenderComponent.h"
#include "CollisionComponent.h"
#include "GameInstance.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "Input.h"
#include "InputManager.h"
#include "PepperComponent.h"
#include "ScoreComponent.h"
#include "Scene.h"
#include "EnumClasses.h"

dae::PeterPepperJr::PeterPepperJr(dae::Scene& scene, Vector2 loc, bool keyboardControls)
{
	Initialize(scene, loc, keyboardControls);
}

void dae::PeterPepperJr::Initialize(dae::Scene& scene, Vector2 loc, bool keyboardControls)
{
	auto go = std::make_shared<dae::GameObject>();
	m_PeterJr = go.get();
	go->SetTag(Tag::peterjr);
	go->AddComponent<PepperComponent>();

	go->AddComponent<dae::CollisionComponent>()->SetSize(32, 32);

	auto rc = go->AddComponent<dae::AnimationRenderComponent>();
	rc->SetTexture("\\Sprites\\PeterPepper\\sprites.png");
	rc->SetDimensions(m_Height, m_Width);
	rc->SetSpriteDimensions(16, 16);

	go->AddComponent<dae::PeterPepperComponent>()->InitAnimation(rc);
	go->GetTransform()->SetLocalPosition(loc.x, loc.y, 0);

	scene.Add(go);

	if (keyboardControls)
	{

		auto keyBoardKey = Input::KeyCommand(SDL_SCANCODE_LEFT,KeyState::OnPressed);
		auto controllerkey = Input::ControllerKey({ 1, ControllerButton::DpadLeft,KeyState::OnPressed });
		auto command = std::make_shared<dae::MoveLeft>(go);
		dae::InputManager::GetInstance().AddCommand(controllerkey, command);
		dae::InputManager::GetInstance().AddCommand(keyBoardKey, command);

		keyBoardKey = Input::KeyCommand(SDL_SCANCODE_LEFT, KeyState::OnReleased);
		controllerkey = Input::ControllerKey({ 1,ControllerButton::DpadLeft,KeyState::OnReleased });
		auto idlecommand = std::make_shared<dae::Idle>(go);
		dae::InputManager::GetInstance().AddCommand(controllerkey, idlecommand);
		dae::InputManager::GetInstance().AddCommand(keyBoardKey, idlecommand);

		//RIGHT

		keyBoardKey = Input::KeyCommand(SDL_SCANCODE_RIGHT, KeyState::OnPressed);
		controllerkey = Input::ControllerKey({ 1, ControllerButton::DpadRight,KeyState::OnPressed });
		auto command2 = std::make_shared<dae::MoveRight>(go);
		dae::InputManager::GetInstance().AddCommand(controllerkey, command2);
		dae::InputManager::GetInstance().AddCommand(keyBoardKey, command2);

		keyBoardKey = Input::KeyCommand(SDL_SCANCODE_RIGHT, KeyState::OnReleased);
		controllerkey = Input::ControllerKey({ 1, ControllerButton::DpadRight,KeyState::OnReleased });
		dae::InputManager::GetInstance().AddCommand(controllerkey, idlecommand);
		dae::InputManager::GetInstance().AddCommand(keyBoardKey, idlecommand);

		//UP
		keyBoardKey = Input::KeyCommand(SDL_SCANCODE_UP, KeyState::OnPressed);
		controllerkey = Input::ControllerKey({ 1, ControllerButton::DpadUp,KeyState::OnPressed });
		auto command3 = std::make_shared<dae::MoveUp>(go);
		dae::InputManager::GetInstance().AddCommand(controllerkey, command3);
		dae::InputManager::GetInstance().AddCommand(keyBoardKey, command3);

		keyBoardKey = Input::KeyCommand(SDL_SCANCODE_UP, KeyState::OnReleased);
		controllerkey = Input::ControllerKey({ 1, ControllerButton::DpadUp,KeyState::OnReleased });
		dae::InputManager::GetInstance().AddCommand(controllerkey, idlecommand);
		dae::InputManager::GetInstance().AddCommand(keyBoardKey, idlecommand);

		//DOWN
		keyBoardKey = Input::KeyCommand(SDL_SCANCODE_DOWN, KeyState::OnPressed);
		controllerkey = Input::ControllerKey({ 1, ControllerButton::DpadDown,KeyState::OnPressed });
		auto command4 = std::make_shared<dae::MoveDown>(go);
		dae::InputManager::GetInstance().AddCommand(controllerkey, command4);
		dae::InputManager::GetInstance().AddCommand(keyBoardKey, command4);

		keyBoardKey = Input::KeyCommand(SDL_SCANCODE_DOWN, KeyState::OnReleased);
		controllerkey = Input::ControllerKey({ 1, ControllerButton::DpadDown,KeyState::OnReleased });
		dae::InputManager::GetInstance().AddCommand(controllerkey, idlecommand);
		dae::InputManager::GetInstance().AddCommand(keyBoardKey, idlecommand);

		//PEPPER
		keyBoardKey = Input::KeyCommand(SDL_SCANCODE_SPACE, KeyState::OnPressed);
		controllerkey = Input::ControllerKey({ 1, ControllerButton::ButtonA,KeyState::OnPressed });
		auto command5 = std::make_shared<dae::Pepper>(go);
		dae::InputManager::GetInstance().AddCommand(controllerkey, command5);
		dae::InputManager::GetInstance().AddCommand(keyBoardKey, command5);
	}
	else
	{
		auto controllerkey = Input::ControllerKey({ 1,ControllerButton::DpadLeft,KeyState::OnPressed });
		auto command = std::make_shared<dae::MoveLeft>(go);
		dae::InputManager::GetInstance().AddCommand(controllerkey, command);

		controllerkey = Input::ControllerKey({ 1, ControllerButton::DpadLeft,KeyState::OnReleased });
		auto idlecommand = std::make_shared<dae::Idle>(go);
		dae::InputManager::GetInstance().AddCommand(controllerkey, idlecommand);

		//RIGHT
		controllerkey = Input::ControllerKey({ 1, ControllerButton::DpadRight,KeyState::OnPressed });
		auto command2 = std::make_shared<dae::MoveRight>(go);
		dae::InputManager::GetInstance().AddCommand(controllerkey, command2);

		controllerkey = Input::ControllerKey({ 1, ControllerButton::DpadRight,KeyState::OnReleased });
		dae::InputManager::GetInstance().AddCommand(controllerkey, idlecommand);

		//UP
		controllerkey = Input::ControllerKey({ 1, ControllerButton::DpadUp,KeyState::OnPressed });
		auto command3 = std::make_shared<dae::MoveUp>(go);
		dae::InputManager::GetInstance().AddCommand(controllerkey, command3);
		 
		controllerkey = Input::ControllerKey({ 1, ControllerButton::DpadUp,KeyState::OnReleased });
		dae::InputManager::GetInstance().AddCommand(controllerkey, idlecommand);

		//DOWN
		controllerkey = Input::ControllerKey({ 1, ControllerButton::DpadDown,KeyState::OnPressed });
		auto command4 = std::make_shared<dae::MoveDown>(go);
		dae::InputManager::GetInstance().AddCommand(controllerkey, command4);

		controllerkey = Input::ControllerKey({ 1,ControllerButton::DpadDown,KeyState::OnReleased });
		dae::InputManager::GetInstance().AddCommand(controllerkey, idlecommand);

		controllerkey = Input::ControllerKey({ 1,ControllerButton::ButtonA,KeyState::OnPressed });
		auto command5 = std::make_shared<dae::Pepper>(go);
		dae::InputManager::GetInstance().AddCommand(controllerkey, command5);
	}


}

dae::GameObject* dae::PeterPepperJr::GetGameObject()
{
	return m_PeterJr;
}

