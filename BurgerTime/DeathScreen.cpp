#include "DeathScreen.h"

#include "GameInstance.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ServiceLocator.h"
#include "TextComponent.h"
#include "TransitionComponent.h"

DeathScreen::DeathScreen()
{
	Initialize();
}

void DeathScreen::Initialize()
{
	dae::ServiceLocator::GetSoundSystem().StopAll();

	int death = dae::ServiceLocator::GetSoundSystem().AddSound("../Data/Sounds/death.wav");
	dae::ServiceLocator::GetSoundSystem().Play(death, 100);

	auto& scene = dae::SceneManager::GetInstance().CreateScene("Death");

	auto go = std::make_shared<dae::GameObject>();
	go->GetTransform()->SetLocalPosition(120, 100, 0);
	go->AddComponent<dae::TransitionComponent>()->SetEnd(true);
	auto text = go->AddComponent<dae::TextComponent>();
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->GetTransform()->SetLocalPosition(220, 400, 0);
	scene.Add(go);

	auto scoreText = go->AddComponent<dae::TextComponent>();

	auto font = dae::ResourceManager::GetInstance().LoadFont("Burgertime.otf", 80);

	text->SetFont(font);
	text->SetText("You died");
	text->SetColor(1, 0, 0, 1);

	font = dae::ResourceManager::GetInstance().LoadFont("Burgertime.otf", 30);

	scoreText->SetFont(font);
	scoreText->SetText("High scores: ");
	scoreText->SetColor(1, 1, 1, 1);

	const std::vector<Player>& players = GameInstance::GetInstance().GetPlayers();

	if (players.size() > 0)
	{
		auto score1 = go->AddComponent<dae::TextComponent>();
		score1->SetFont(font);
		score1->SetOffset(0, 70);
		score1->SetText(players.at(0).name + ": " + std::to_string(players.at(0).score));
		score1->SetColor(1, 1, 1, 1);
	}

	if (players.size() > 1)
	{
		auto score2 = go->AddComponent<dae::TextComponent>();
		score2->SetFont(font);
		score2->SetOffset(0, 140);
		score2->SetText(players.at(1).name + ": " + std::to_string(players.at(1).score));
		score2->SetColor(1, 1, 1, 1);
	}

	if (players.size() > 2)
	{
		auto score3 = go->AddComponent<dae::TextComponent>();
		score3->SetFont(font);
		score3->SetOffset(0, 210);
		score3->SetText(players.at(2).name + ": " + std::to_string(players.at(2).score));
		score3->SetColor(1, 1, 1, 1);
	}

}
