#include "Game.h"

#include "GameInstance.h"
#include "MenuScreen.h"
#include "NextScreen.h"

void Game::LoadGame()
{
	GameInstance::GetInstance().StartGame();
	MenuScreen{};
}


void Game::Cleanup()
{
	GameInstance::GetInstance().EndGame();
	Minigin::Cleanup();
}
