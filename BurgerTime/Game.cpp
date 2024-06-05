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
#include "TopBun.h"
#include "Cheese.h"
#include "BottomBun.h"
#include "Lettuce.h"
#include "Plate.h"
#include "Patty.h"
#include "Tomato.h"

void Game::LoadGame()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	dae::PeterPepper peter{ scene };
	dae::Platform plat{ scene,Vector2{0,0} };
	dae::Platform plat2{ scene,Vector2{64,0} };
	dae::Platform plat3{ scene,Vector2{0,128} };
	dae::Platform plat4{ scene,Vector2{64,128} };
	dae::Platform plat41{ scene,Vector2{128,64} };
	dae::Platform plat5{ scene,Vector2{128,196} };
	dae::Platform plat6{ scene,Vector2{64,64} };
	dae::Ladder ladder2{ scene,Vector2{64,64} };
	dae::Ladder ladder{ scene,Vector2{64,0} };
	dae::Ladder ladder3{ scene,Vector2{64,128} };
	dae::Ladder ladder4{ scene,Vector2{64,192} };
	dae::Ladder ladder5{ scene,Vector2{64,256} };
	dae::Ladder ladder6{ scene,Vector2{64,320} };
	dae::Platform plat7{ scene,Vector2{128,0} };
	dae::Platform plat8{ scene,Vector2{128,64} };
	dae::Platform plat9{ scene,Vector2{128,128} };
	dae::Platform plat10{ scene,Vector2{128,196} };
	dae::Platform plat11{ scene,Vector2{128,256} };
	dae::Platform plat12{ scene,Vector2{128,320} };

	dae::TopBun bun{ scene, Vector2{128,0} };
	dae::Cheese cheese{ scene, Vector2{128,64} };
	dae::Patty patty{ scene,Vector2{128,128} };
	dae::Tomato tomato{ scene, Vector2{128,192} };
	dae::Lettuce lettuce{ scene, Vector2{128,256} };
	dae::BottomBun botbun{ scene, Vector2{128,320} };
	dae::Plate plate{ scene, Vector2{128,384} };
}