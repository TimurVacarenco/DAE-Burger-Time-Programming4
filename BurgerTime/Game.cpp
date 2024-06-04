#include "Game.h"

#include "FPSComponent.h"
#include "Minigin.h"
#include "GameObject.h"
#include "HealthDisplayComponent.h"
#include "InputManager.h"
#include "PepperComponent.h"
#include "ScoreDisplayComponent.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "TextComponent.h"
#include "RenderComponent.h"
#include "ServiceLocator.h"
#include "PeterPepper.h"
#include "Platform.h"
#include "Ladder.h"
#include "Wall.h"

void Game::LoadGame()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	dae::PeterPepper peter{ scene };
	dae::Platform plat{ scene,Vector2{0,0} };
	dae::Platform plat2{ scene,Vector2{64,0} };
	dae::Ladder ladder2{ scene,Vector2{64,64} };
	dae::Ladder ladder{ scene,Vector2{64,0} };
	dae::Wall wall{ scene,Vector2{64,128} };
}