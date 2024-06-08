#include "NextScreen.h"

#include "GameInstance.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ServiceLocator.h"
#include "TextComponent.h"
#include "TransitionComponent.h"

NextScreen::NextScreen()
{
	Initialize();
}

void NextScreen::Initialize()
{
	dae::ServiceLocator::GetSoundSystem().StopAll();

	int win = dae::ServiceLocator::GetSoundSystem().AddSound("../Data/Sounds/win.wav");
	dae::ServiceLocator::GetSoundSystem().Play(win, 100);

	auto& scene = dae::SceneManager::GetInstance().CreateScene("Win!");

	auto go = std::make_shared<dae::GameObject>();
	go->GetTransform()->SetLocalPosition(170, 100, 0);
	go->AddComponent<dae::TransitionComponent>();
	auto text = go->AddComponent<dae::TextComponent>();
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->GetTransform()->SetLocalPosition(280, 400, 0);
	scene.Add(go);

	auto scoreText = go->AddComponent<dae::TextComponent>();

	auto font = dae::ResourceManager::GetInstance().LoadFont("Burgertime.otf", 80);

	text->SetFont(font);
	text->SetText("Level " + std::to_string(GameInstance::GetInstance().GetLevelNr()));
	text->SetColor(1, 1, 1, 1);


	font = dae::ResourceManager::GetInstance().LoadFont("Burgertime.otf", 30);
	scoreText->SetFont(font);
	scoreText->SetText("Score: " + std::to_string(GameInstance::GetInstance().GetScore()));
	scoreText->SetColor(1, 1, 1, 1);
}
