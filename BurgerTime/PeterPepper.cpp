#include "PeterPepper.h"

#include "RenderComponent.h"
#include "GameObject.h"
#include "Input.h"
#include "InputManager.h"
#include "Scene.h"
#include "ServiceLocator.h"

dae::PeterPepper::PeterPepper(dae::Scene& scene)
{
	Initialize(scene);
}

void dae::PeterPepper::Initialize(dae::Scene& scene)
{
	auto go = std::make_shared<dae::GameObject>();
	auto rc = go->AddComponent<dae::RenderComponent>();
	go->AddComponent<PepperComponent>();
	rc->SetTexture("\\Sprites\\PeterPepper\\peter.png");

	scene.Add(go);

	InputManager::GetInstance().AddController(1);
	auto controllerkey = Input::ControllerKey({ 0, ControllerButton::DpadLeft,KeyState::OnPressed });
	auto command = std::make_unique<dae::MoveLeft>(go);
	dae::InputManager::GetInstance().AddCommand(controllerkey, std::move(command));

	controllerkey = Input::ControllerKey({ 0, ControllerButton::DpadLeft,KeyState::OnReleased });
	auto command2 = std::make_unique<dae::Idle>(go);
	dae::InputManager::GetInstance().AddCommand(controllerkey, std::move(command2));


	controllerkey = Input::ControllerKey({ 0, ControllerButton::DpadRight,KeyState::OnPressed });
	auto command3 = std::make_unique<dae::MoveRight>(go);
	dae::InputManager::GetInstance().AddCommand(controllerkey, std::move(command3));

	controllerkey = Input::ControllerKey({ 0, ControllerButton::DpadRight,KeyState::OnReleased });
	auto command21 = std::make_unique<dae::Idle>(go);
	dae::InputManager::GetInstance().AddCommand(controllerkey, std::move(command21));

	controllerkey = Input::ControllerKey({ 0, ControllerButton::DpadUp,KeyState::OnPressed });
	auto command4 = std::make_unique<dae::MoveUp>(go);
	dae::InputManager::GetInstance().AddCommand(controllerkey, std::move(command4));

	controllerkey = Input::ControllerKey({ 0, ControllerButton::DpadUp,KeyState::OnReleased });
	auto command22 = std::make_unique<dae::Idle>(go);
	dae::InputManager::GetInstance().AddCommand(controllerkey, std::move(command22));

	controllerkey = Input::ControllerKey({ 0, ControllerButton::DpadDown,KeyState::OnPressed });
	auto command5 = std::make_unique<dae::MoveDown>(go);
	dae::InputManager::GetInstance().AddCommand(controllerkey, std::move(command5));

	controllerkey = Input::ControllerKey({ 0, ControllerButton::DpadDown,KeyState::OnReleased });
	auto command23 = std::make_unique<dae::Idle>(go);
	dae::InputManager::GetInstance().AddCommand(controllerkey, std::move(command23));

}