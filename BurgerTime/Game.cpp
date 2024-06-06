#include "Game.h"

#include "SceneManager.h"
#include "Level.h"

void Game::LoadGame()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Level1");
	dae::Level level{ scene };
}