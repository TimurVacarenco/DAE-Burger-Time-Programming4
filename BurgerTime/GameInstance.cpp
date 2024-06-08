#include "GameInstance.h"
#include "SceneManager.h"
#include "Scene.h"
#include "LevelLoader.h"
#include <ScoreComponent.h>
#include <GameObject.h>
#include "InputManager.h"
#include <ServiceLocator.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "NextScreen.h"
#include "LifeLostScreen.h"
#include "DeathScreen.h"
#include "MenuScreen.h"

void GameInstance::SetPlates(int amt)
{
	m_Plates = amt;
	m_FullPlates = 0;
}

void GameInstance::FillPlate()
{
	++m_FullPlates;
	if (m_FullPlates >= m_Plates)
	{
		auto& scene = dae::SceneManager::GetInstance().GetActiveScene();
		dae::SceneManager::GetInstance().RemoveScene(scene);
		++m_LevelIdx;
		if (m_LevelIdx > 3)
		{
			m_LevelIdx = 1;
		}
		NextScreen{};
	}
}

void GameInstance::Hit(int lives, int points)
{
	m_Lives = lives;
	if (points > m_HighScore)
	{
		m_HighScore = points;
	}
	m_Score = 0;
	LifeLostScreen{};
}

void GameInstance::Died(int points)
{

	if (points > m_HighScore)
	{
		m_HighScore = points;
	}
	m_HighScore = points;
	SavePlayerToFile();
	LoadPlayersFromFile();
	m_HighScore = 0;
	m_Score = 0;
	auto& scene = dae::SceneManager::GetInstance().GetActiveScene();
	dae::SceneManager::GetInstance().RemoveScene(scene);
	DeathScreen{};
}

void GameInstance::ReloadLevel()
{
	if (m_LevelIdx == 1)
	{
		LevelLoader::ReloadLevel("../Data/Levels/level1.json");
	}
	else if (m_LevelIdx == 2)
	{
		LevelLoader::ReloadLevel("../Data/Levels/level2.json");
	}
	else if (m_LevelIdx == 3)
	{
		LevelLoader::ReloadLevel("../Data/Levels/level3.json");
	}
}

void GameInstance::LoadNextLevel()
{
	for (auto object : dae::SceneManager::GetInstance().GetActiveScene().GetObjects())
	{
		if (object->GetTag() == Tag::peter)
		{
			m_Score = object->GetComponent<dae::ScoreComponent>()->GetPoints();
		}
	}
	switch (m_LevelIdx)
	{
	case 1:
		LevelLoader::LoadLevel("../Data/Levels/level1.json");
		break;
	case 2:
		LevelLoader::LoadLevel("../Data/Levels/level2.json");
		break;
	case 3:
		LevelLoader::LoadLevel("../Data/Levels/level3.json");
		break;
	}

}

void GameInstance::SkipLevel()
{
	dae::ServiceLocator::GetSoundSystem().StopAll();
	auto& scene = dae::SceneManager::GetInstance().GetActiveScene();
	dae::SceneManager::GetInstance().RemoveScene(scene);
	++m_LevelIdx;
	if (m_LevelIdx > 3)
	{
		m_LevelIdx = 1;
	}
	LoadNextLevel();
}

void GameInstance::StartGame()
{
	LoadPlayersFromFile();
}

void GameInstance::EndGame()
{
	for (auto object : dae::SceneManager::GetInstance().GetActiveScene().GetObjects())
	{
		if (object->GetTag() == Tag::peter)
		{
			m_Score = object->GetComponent<dae::ScoreComponent>()->GetPoints();
		}
	}
	auto& scene = dae::SceneManager::GetInstance().GetActiveScene();
	dae::SceneManager::GetInstance().RemoveScene(scene);
	dae::InputManager::GetInstance().RemoveCommands();
	if (m_Score > m_HighScore)
	{
		m_HighScore = m_Score;
	}
	m_HighScore = m_Score;
	SavePlayerToFile();
	MenuScreen{};
}

void GameInstance::SavePlayerToFile()
{
	std::ofstream outputFile("../Data/scores.txt", std::ios::app);

	if (outputFile.is_open()) 
	{
		outputFile << m_Name << "," << m_HighScore << std::endl;
		outputFile.close();
	}
}

void GameInstance::LoadPlayersFromFile()
{
	std::ifstream inputFile("../Data/scores.txt");

	if (inputFile.is_open()) 
	{
		Player player;
		while (getline(inputFile, player.name, ',')) 
		{
			inputFile >> player.score;
			inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			m_Players.push_back(player);
		}
		std::sort(m_Players.begin(), m_Players.end(), [](const Player& a, const Player& b) {
			return a.score > b.score; });
	}
}
