#include "PlayerHotDog.h"

#include "AnimationRenderComponent.h"
#include "CollisionComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "Input.h"
#include "InputManager.h"
#include "PlayerHotDogComponent.h"
#include "Scene.h"
#include "EnumClasses.h"

dae::PlayerHotDog::PlayerHotDog(dae::Scene& scene, Vector2 loc, bool keyboardControls)
{
	Initialize(scene, loc, keyboardControls);
}

void dae::PlayerHotDog::Initialize(dae::Scene& scene, Vector2 loc, bool keyboardControls)
{
	auto go = std::make_shared<dae::GameObject>();
	m_PlayerHotDog = go.get();
	go->SetTag(Tag::playerhotdog);

	go->AddComponent<dae::CollisionComponent>()->SetSize(32, 32);

	auto rc = go->AddComponent<dae::AnimationRenderComponent>();
	rc->SetTexture("\\Sprites\\Enemies\\dog.png");
	rc->SetDimensions(m_Height, m_Width);
	rc->SetSpriteDimensions(16, 16);

	go->AddComponent<dae::PlayerHotDogComponent>()->InitAnimation(rc);
	go->GetTransform()->SetLocalPosition(loc.x, loc.y, 0);

	scene.Add(go);

	if (keyboardControls)
	{

		auto keyBoardKey = Input::KeyCommand(SDL_SCANCODE_LEFT, KeyState::OnPressed);
		auto controllerkey = Input::ControllerKey({ 1, ControllerButton::DpadLeft,KeyState::OnPressed });
		auto command = std::make_shared<dae::HotDogMoveLeft>(go);
		dae::InputManager::GetInstance().AddCommand(controllerkey, command);
		dae::InputManager::GetInstance().AddCommand(keyBoardKey, command);

		keyBoardKey = Input::KeyCommand(SDL_SCANCODE_LEFT, KeyState::OnReleased);
		controllerkey = Input::ControllerKey({ 1, ControllerButton::DpadLeft,KeyState::OnReleased });
		auto idlecommand = std::make_shared<dae::HotDogIdle>(go);
		dae::InputManager::GetInstance().AddCommand(controllerkey, idlecommand);
		dae::InputManager::GetInstance().AddCommand(keyBoardKey, idlecommand);

		keyBoardKey = Input::KeyCommand(SDL_SCANCODE_RIGHT,KeyState::OnPressed);
		controllerkey = Input::ControllerKey({ 1, ControllerButton::DpadRight,KeyState::OnPressed });
		auto command2 = std::make_shared<dae::HotDogMoveRight>(go);
		dae::InputManager::GetInstance().AddCommand(controllerkey, command2);
		dae::InputManager::GetInstance().AddCommand(keyBoardKey, command2);

		keyBoardKey = Input::KeyCommand(SDL_SCANCODE_RIGHT, KeyState::OnReleased);
		controllerkey = Input::ControllerKey({ 1, ControllerButton::DpadRight,KeyState::OnReleased });
		dae::InputManager::GetInstance().AddCommand(controllerkey, idlecommand);
		dae::InputManager::GetInstance().AddCommand(keyBoardKey, idlecommand);

		keyBoardKey = Input::KeyCommand(SDL_SCANCODE_UP, KeyState::OnPressed);
		controllerkey = Input::ControllerKey({ 1, ControllerButton::DpadUp,KeyState::OnPressed });
		auto command3 = std::make_shared<dae::HotDogMoveUp>(go);
		dae::InputManager::GetInstance().AddCommand(controllerkey, command3);
		dae::InputManager::GetInstance().AddCommand(keyBoardKey, command3);

		keyBoardKey = Input::KeyCommand(SDL_SCANCODE_UP, KeyState::OnReleased);
		controllerkey = Input::ControllerKey({ 1, ControllerButton::DpadUp,KeyState::OnReleased });
		dae::InputManager::GetInstance().AddCommand(controllerkey, idlecommand);
		dae::InputManager::GetInstance().AddCommand(keyBoardKey, idlecommand);

		keyBoardKey = Input::KeyCommand(SDL_SCANCODE_DOWN, KeyState::OnPressed);
		controllerkey = Input::ControllerKey({ 1, ControllerButton::DpadDown,KeyState::OnPressed });
		auto command4 = std::make_shared<dae::HotDogMoveDown>(go);
		dae::InputManager::GetInstance().AddCommand(controllerkey, command4);
		dae::InputManager::GetInstance().AddCommand(keyBoardKey, command4);

		keyBoardKey = Input::KeyCommand(SDL_SCANCODE_DOWN, KeyState::OnReleased);
		controllerkey = Input::ControllerKey({ 1, ControllerButton::DpadDown,KeyState::OnReleased });
		dae::InputManager::GetInstance().AddCommand(controllerkey, idlecommand);
		dae::InputManager::GetInstance().AddCommand(keyBoardKey, idlecommand);

	}
	else
	{
		auto controllerkey = Input::ControllerKey({ 1, ControllerButton::DpadLeft,KeyState::OnPressed });
		auto command = std::make_shared<dae::HotDogMoveLeft>(go);
		dae::InputManager::GetInstance().AddCommand(controllerkey, command);

		controllerkey = Input::ControllerKey({ 1, ControllerButton::DpadLeft,KeyState::OnReleased });
		auto idlecommand = std::make_shared<dae::HotDogIdle>(go);
		dae::InputManager::GetInstance().AddCommand(controllerkey, idlecommand);

		controllerkey = Input::ControllerKey({ 1, ControllerButton::DpadRight,KeyState::OnPressed });
		auto command2 = std::make_shared<dae::HotDogMoveRight>(go);
		dae::InputManager::GetInstance().AddCommand(controllerkey, command2);

		controllerkey = Input::ControllerKey({ 1, ControllerButton::DpadRight,KeyState::OnReleased });
		dae::InputManager::GetInstance().AddCommand(controllerkey, idlecommand);

		controllerkey = Input::ControllerKey({ 1, ControllerButton::DpadUp, KeyState::OnPressed });
		auto command3 = std::make_shared<dae::HotDogMoveUp>(go);
		dae::InputManager::GetInstance().AddCommand(controllerkey, command3);

		controllerkey = Input::ControllerKey({ 1, ControllerButton::DpadUp,KeyState::OnReleased });
		dae::InputManager::GetInstance().AddCommand(controllerkey, idlecommand);

		controllerkey = Input::ControllerKey({ 1, ControllerButton::DpadDown,KeyState::OnPressed });
		auto command4 = std::make_shared<dae::HotDogMoveDown>(go);
		dae::InputManager::GetInstance().AddCommand(controllerkey, command4);

		controllerkey = Input::ControllerKey({ 1,ControllerButton::DpadDown, KeyState::OnReleased });
		dae::InputManager::GetInstance().AddCommand(controllerkey, idlecommand);

	}

}

dae::GameObject* dae::PlayerHotDog::GetGameObject()
{
	return m_PlayerHotDog;
}

