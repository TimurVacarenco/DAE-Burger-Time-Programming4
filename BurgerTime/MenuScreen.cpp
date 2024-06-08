#include "MenuScreen.h"

#include "GameObject.h"
#include "InputManager.h"
#include "MenuComponent.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "TextComponent.h"

MenuScreen::MenuScreen()
{
	Initialize();
}

void MenuScreen::Initialize()
{
	auto go = std::make_shared<dae::GameObject>();
	go->GetTransform()->SetLocalPosition(100, 200, 0);
	auto fontsmall = dae::ResourceManager::GetInstance().LoadFont("Burgertime.otf", 40);
	auto font = dae::ResourceManager::GetInstance().LoadFont("Burgertime.otf", 60);
	auto fontbig = dae::ResourceManager::GetInstance().LoadFont("Burgertime.otf", 100);


	auto title = go->AddComponent<dae::TextComponent>();
	auto sptext = go->AddComponent<dae::TextComponent>();
	auto cooptext = go->AddComponent<dae::TextComponent>();
	auto vstext = go->AddComponent<dae::TextComponent>();
	auto nametext = go->AddComponent<dae::TextComponent>();

	std::vector<dae::TextComponent*> textcomps;
	textcomps.push_back(sptext);
	textcomps.push_back(cooptext);
	textcomps.push_back(vstext);
	textcomps.push_back(nametext);

	nametext->SetFont(fontsmall);
	title->SetFont(fontbig);
	sptext->SetFont(font);
	cooptext->SetFont(font);
	vstext->SetFont(font);

	title->SetText("BurgerTime");
	title->SetColor(1, 1, 1, 1);
	title->SetOffset(-50, -150);

	sptext->SetText("Single player");
	sptext->SetColor(1, 0, 0, 1);

	cooptext->SetText("Cooperative");
	cooptext->SetColor(1, 1, 1, 1);
	cooptext->SetOffset(0, 70);

	vstext->SetText("Versus");
	vstext->SetColor(1, 1, 1, 1);
	vstext->SetOffset(0, 140);

	nametext->SetText("Select gamemode");
	nametext->SetColor(1, 1, 1, 1);
	nametext->SetOffset(0, 270);

	auto menu = go->AddComponent<dae::MenuComponent>();
	menu->SetTextComps(textcomps);

	auto keyBoardKey = Input::KeyCommand(SDL_SCANCODE_DOWN, KeyState::OnReleased);
	auto controllerkey = Input::ControllerKey({ 0,ControllerButton::DpadDown,KeyState::OnReleased });
	auto command = std::make_shared<dae::MenuNext>(go);
	dae::InputManager::GetInstance().AddCommand(controllerkey, command);
	dae::InputManager::GetInstance().AddCommand(keyBoardKey, command);

	keyBoardKey = Input::KeyCommand(SDL_SCANCODE_UP, KeyState::OnReleased);
	controllerkey = Input::ControllerKey({ 0, ControllerButton::DpadUp,KeyState::OnReleased });
	auto command2 = std::make_shared<dae::MenuPrevious>(go);
	dae::InputManager::GetInstance().AddCommand(controllerkey, command2);
	dae::InputManager::GetInstance().AddCommand(keyBoardKey, command2);

	keyBoardKey = Input::KeyCommand(SDL_SCANCODE_SPACE, KeyState::OnReleased);
	controllerkey = Input::ControllerKey({ 0, ControllerButton::ButtonA,KeyState::OnReleased });
	auto command3 = std::make_shared<dae::MenuStart>(go);
	dae::InputManager::GetInstance().AddCommand(controllerkey, command3);
	dae::InputManager::GetInstance().AddCommand(keyBoardKey, command3);

	keyBoardKey = Input::KeyCommand(SDL_SCANCODE_RETURN,KeyState::OnReleased);
	dae::InputManager::GetInstance().AddCommand(keyBoardKey, command3);


	auto& scene = dae::SceneManager::GetInstance().CreateScene("MENU");
	scene.Add(go);
}
