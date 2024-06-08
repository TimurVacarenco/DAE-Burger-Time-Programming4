#include "LifeLostScreen.h"

#include "GameInstance.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ServiceLocator.h"
#include "TextComponent.h"
#include "TransitionComponent.h"

LifeLostScreen::LifeLostScreen()
{
	Initialize();
}

void LifeLostScreen::Initialize()
{
	dae::ServiceLocator::GetSoundSystem().StopAll();
	int death = dae::ServiceLocator::GetSoundSystem().AddSound("../Data/Sounds/death.wav");
	dae::ServiceLocator::GetSoundSystem().Play(death, 100);

	auto& scene = dae::SceneManager::GetInstance().CreateScene("Life lost");

	auto go = std::make_shared<dae::GameObject>();
	go->GetTransform()->SetLocalPosition(120, 100, 0);

	auto trans = go->AddComponent<dae::TransitionComponent>();
	trans->SetTransitionTime(2.f);
	trans->SetReload(true);

	auto text = go->AddComponent<dae::TextComponent>();
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->GetTransform()->SetLocalPosition(220, 400, 0);
	scene.Add(go);

	auto scoreText = go->AddComponent<dae::TextComponent>();

	auto font = dae::ResourceManager::GetInstance().LoadFont("Burgertime.otf", 80);

	text->SetFont(font);
	text->SetText("Life lost");
	text->SetColor(1, 0, 0, 1);


	font = dae::ResourceManager::GetInstance().LoadFont("Burgertime.otf", 30);
	scoreText->SetFont(font);
	scoreText->SetText("Lives: " + std::to_string(GameInstance::GetInstance().GetLives()));
	scoreText->SetColor(1, 1, 1, 1);
}


