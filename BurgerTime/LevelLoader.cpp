#include "LevelLoader.h"
#include <fstream>
#include <rapidjson.h>
#include <document.h>

#include "BottomBun.h"
#include "TopBun.h"
#include "Cheese.h"
#include "EnemySpawner.h"
#include "GameInstance.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "HealthDisplayComponent.h"
#include "InputManager.h"
#include "istreamwrapper.h"
#include "Ladder.h"
#include "Lettuce.h"
#include "Patty.h"
#include "PepperComponent.h"
#include "PepperDisplayComponent.h"
#include "PeterPepper.h"
#include "PeterPepperJr.h"
#include "Plate.h"
#include "Platform.h"
#include "PlayerHotDog.h"
#include "ScoreComponent.h"
#include "ScoreDisplayComponent.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ServiceLocator.h"
#include "Tomato.h"
#include <unordered_map>

int HashString(const std::string& str)
{
	static std::unordered_map<std::string, int> hashTable = {
		{"platform", 1},
		{"ladder", 2},
		{"bun", 3},
		{"lettuce", 4},
		{"patty", 5},
		{"cheese", 6},
		{"tomato", 7},
		{"bottombun", 8},
		{"plate", 9},
		{"peter", 10},
		{"peterjr", 11},
		{"playerdog", 12},
		{"enemy", 13}
	};

	auto it = hashTable.find(str);
	if (it != hashTable.end())
	{
		return it->second;
	}
	return -1; 
}

void LevelLoader::ReloadLevel(const std::string& fileLoc)
{

	dae::ServiceLocator::GetSoundSystem().StopAll();
	auto& sceneDel = dae::SceneManager::GetInstance().GetActiveScene();
	dae::SceneManager::GetInstance().RemoveScene(sceneDel);

	int lives = GameInstance::GetInstance().GetLives();

	dae::InputManager::GetInstance().RemoveCommands();
	auto& scene = dae::SceneManager::GetInstance().CreateScene("LEVEL");
	int music = dae::ServiceLocator::GetSoundSystem().AddSound("../Data/Sounds/music.wav");
	dae::ServiceLocator::GetSoundSystem().Play(music, 100, true);

	if (std::ifstream is{ fileLoc })
	{
		rapidjson::IStreamWrapper isw{ is };
		rapidjson::Document jsonDoc;
		jsonDoc.ParseStream(isw);

		std::vector<Vector2> bounds{};
		int plates{};
		dae::GameObject* petergo = nullptr;

		using rapidjson::Value;
		for (Value::ConstValueIterator itr = jsonDoc.Begin(); itr != jsonDoc.End(); ++itr)
		{
			const Value& pos = *itr;
			std::string type = pos["type"].GetString();
			const Value& locs = pos["positions"].GetArray();
			int hashValue = HashString(type);
			for (rapidjson::SizeType i = 0; i < locs.Size(); i++)
			{
				const Value& x = locs[i][0];
				const Value& y = locs[i][1];
				switch (hashValue)
				{
				case 1: // platform
				{
					dae::Platform{ scene,{x.GetFloat(), y.GetFloat()} };
					break;
				}
				case 2: // ladder
				{
					dae::Ladder{ scene,{x.GetFloat(), y.GetFloat()} };
					break;
				}
				case 3: // bun
				{
					dae::TopBun{ scene,{x.GetFloat(), y.GetFloat()} };
					break;
				}
				case 4: // lettuce
				{
					dae::Lettuce{ scene,{x.GetFloat(), y.GetFloat()} };
					break;
				}
				case 5: // patty
				{
					dae::Patty{ scene,{x.GetFloat(), y.GetFloat()} };
					break;
				}
				case 6: // cheese
				{
					dae::Cheese{ scene,{x.GetFloat(), y.GetFloat()} };
					break;
				}
				case 7: // tomato
				{
					dae::Tomato{ scene,{x.GetFloat(), y.GetFloat()} };
					break;
				}
				case 8: // bottombun
				{
					{
						dae::BottomBun{ scene,{x.GetFloat(), y.GetFloat()} };
						break;
					}
				}
				case 9: // plate
				{
					dae::Plate{ scene,{x.GetFloat(), y.GetFloat()} };
					++plates;
					break;
				}
				case 10://peter
				{
					if (GameInstance::GetInstance().GetGameMode() != GameMode::singleplayer)
					{
						dae::PeterPepper peter{ scene,{x.GetFloat(),y.GetFloat()},false };
						petergo = peter.GetGameObject();
						petergo->GetComponent<dae::HealthComponent>()->SetLives(lives);

						auto go = std::make_shared<dae::GameObject>();
						go->GetTransform()->SetLocalPosition(80, 850, 0);

						auto pointsdisp = go->AddComponent<dae::ScoreDisplayComponent>();
						pointsdisp->SetActorToDisplay(petergo);
						petergo->GetComponent<dae::ScoreComponent>()->AddObserver(pointsdisp);
						scene.Add(go);

						go = std::make_shared<dae::GameObject>();
						go->GetTransform()->SetLocalPosition(550, 850, 0);
						auto healthdisp = go->AddComponent<dae::HealthDisplayComponent>();
						healthdisp->SetActorToDisplay(petergo);
						petergo->GetComponent<dae::HealthComponent>()->AddObserver(healthdisp);
						scene.Add(go);

						go = std::make_shared<dae::GameObject>();
						go->GetTransform()->SetLocalPosition(560, 820, 0);
						auto pepperdisp = go->AddComponent<dae::PepperDisplayComponent>();
						pepperdisp->SetActorToDisplay(petergo);
						petergo->GetComponent<dae::PepperComponent>()->AddObserver(pepperdisp);
						scene.Add(go);
					}
					else
					{
						dae::PeterPepper peter{ scene,{x.GetFloat(),y.GetFloat()} };
						petergo = peter.GetGameObject();
						petergo->GetComponent<dae::HealthComponent>()->SetLives(lives);

						auto go = std::make_shared<dae::GameObject>();
						go->GetTransform()->SetLocalPosition(80, 850, 0);

						auto pointsdisp = go->AddComponent<dae::ScoreDisplayComponent>();
						pointsdisp->SetActorToDisplay(petergo);
						petergo->GetComponent<dae::ScoreComponent>()->AddObserver(pointsdisp);
						scene.Add(go);

						go = std::make_shared<dae::GameObject>();
						go->GetTransform()->SetLocalPosition(550, 850, 0);
						auto healthdisp = go->AddComponent<dae::HealthDisplayComponent>();
						healthdisp->SetActorToDisplay(petergo);
						petergo->GetComponent<dae::HealthComponent>()->AddObserver(healthdisp);
						scene.Add(go);

						go = std::make_shared<dae::GameObject>();
						go->GetTransform()->SetLocalPosition(560, 820, 0);
						auto pepperdisp = go->AddComponent<dae::PepperDisplayComponent>();
						pepperdisp->SetActorToDisplay(petergo);
						petergo->GetComponent<dae::PepperComponent>()->AddObserver(pepperdisp);
						scene.Add(go);
					}
				}
				case 11: //peterJr
				{
					if (GameInstance::GetInstance().GetGameMode() == GameMode::coop)
					{
						dae::PeterPepperJr peter{ scene,{x.GetFloat(),y.GetFloat()} };
						auto peterjr = peter.GetGameObject();
						peterjr->GetComponent<dae::PeterPepperComponent>()->SetSecondPlayer(petergo);

						auto go = std::make_shared<dae::GameObject>();
						go->GetTransform()->SetLocalPosition(560, 800, 0);
						auto pepperdisp = go->AddComponent<dae::PepperDisplayComponent>();
						pepperdisp->SetActorToDisplay(peterjr);
						peterjr->GetComponent<dae::PepperComponent>()->AddObserver(pepperdisp);
						scene.Add(go);
					}
					break;
				}
				case 12: //playerHotDog
				{
					if (GameInstance::GetInstance().GetGameMode() == GameMode::versus)
					{
						dae::PlayerHotDog{ scene,{x.GetFloat(),y.GetFloat()} };
					}
					break;
				}
				case 13:
				{
					EnemySpawner{ scene,{x.GetFloat(),y.GetFloat()} };
					break;
				}
				}
			}
			GameInstance::GetInstance().SetPlates(plates);
		}
	}
}
void LevelLoader::LoadLevel(const std::string& fileLoc)
{
	dae::InputManager::GetInstance().RemoveCommands();
	auto& scene = dae::SceneManager::GetInstance().CreateScene("LEVEL");
	int music = dae::ServiceLocator::GetSoundSystem().AddSound("../Data/Sounds/music.wav");
	dae::ServiceLocator::GetSoundSystem().Play(music, 100, true);
	if (std::ifstream is{ fileLoc })
	{
		rapidjson::IStreamWrapper isw{ is };
		rapidjson::Document jsonDoc;
		jsonDoc.ParseStream(isw);

		std::vector<Vector2> bounds{};
		int plates{};
		dae::GameObject* petergo = nullptr;

		using rapidjson::Value;
		for (Value::ConstValueIterator itr = jsonDoc.Begin(); itr != jsonDoc.End(); ++itr)
		{
			const Value& pos = *itr;
			std::string type = pos["type"].GetString();
			const Value& locs = pos["positions"].GetArray();

			int hashValue = HashString(type);
			for (rapidjson::SizeType i = 0; i < locs.Size(); i++)
			{
				const Value& x = locs[i][0];
				const Value& y = locs[i][1];

				switch (hashValue)
				{
				case 1: // platform
				{
					dae::Platform{ scene,{x.GetFloat(), y.GetFloat()} };
					break;
				}
				case 2: // ladder
				{
					dae::Ladder{ scene,{x.GetFloat(), y.GetFloat()} };
					break;
				}
				case 3: // bun
				{
					dae::TopBun{ scene,{x.GetFloat(), y.GetFloat()} };
					break;
				}
				case 4: // lettuce
				{
					dae::Lettuce{ scene,{x.GetFloat(), y.GetFloat()} };
					break;
				}
				case 5: // patty
				{
					dae::Patty{ scene,{x.GetFloat(), y.GetFloat()} };
					break;
				}
				case 6: // cheese
				{
					dae::Cheese{ scene,{x.GetFloat(), y.GetFloat()} };
					break;
				}
				case 7: // tomato
				{
					dae::Tomato{ scene,{x.GetFloat(), y.GetFloat()} };
					break;
				}
				case 8: // bottombun
				{
					{
						dae::BottomBun{ scene,{x.GetFloat(), y.GetFloat()} };
						break;
					}
				}
				case 9: // plate
				{
					dae::Plate{ scene,{x.GetFloat(), y.GetFloat()} };
					++plates;
					break;
				}
				case 10://peter
				{
					if (GameInstance::GetInstance().GetGameMode() != GameMode::singleplayer)
					{
						dae::PeterPepper peter{ scene,{x.GetFloat(),y.GetFloat()},false };
						petergo = peter.GetGameObject();

						auto go = std::make_shared<dae::GameObject>();
						go->GetTransform()->SetLocalPosition(80, 850, 0);

						auto pointsdisp = go->AddComponent<dae::ScoreDisplayComponent>();
						pointsdisp->SetActorToDisplay(petergo);
						petergo->GetComponent<dae::ScoreComponent>()->AddObserver(pointsdisp);
						scene.Add(go);

						go = std::make_shared<dae::GameObject>();
						go->GetTransform()->SetLocalPosition(550, 850, 0);
						auto healthdisp = go->AddComponent<dae::HealthDisplayComponent>();
						healthdisp->SetActorToDisplay(petergo);
						petergo->GetComponent<dae::HealthComponent>()->AddObserver(healthdisp);
						scene.Add(go);

						go = std::make_shared<dae::GameObject>();
						go->GetTransform()->SetLocalPosition(560, 820, 0);
						auto pepperdisp = go->AddComponent<dae::PepperDisplayComponent>();
						pepperdisp->SetActorToDisplay(petergo);
						petergo->GetComponent<dae::PepperComponent>()->AddObserver(pepperdisp);
						scene.Add(go);
					}
					else
					{
						dae::PeterPepper peter{ scene,{x.GetFloat(),y.GetFloat()} };
						petergo = peter.GetGameObject();

						auto go = std::make_shared<dae::GameObject>();
						go->GetTransform()->SetLocalPosition(80, 850, 0);

						auto pointsdisp = go->AddComponent<dae::ScoreDisplayComponent>();
						pointsdisp->SetActorToDisplay(petergo);
						petergo->GetComponent<dae::ScoreComponent>()->AddObserver(pointsdisp);
						scene.Add(go);

						go = std::make_shared<dae::GameObject>();
						go->GetTransform()->SetLocalPosition(550, 850, 0);
						auto healthdisp = go->AddComponent<dae::HealthDisplayComponent>();
						healthdisp->SetActorToDisplay(petergo);
						petergo->GetComponent<dae::HealthComponent>()->AddObserver(healthdisp);
						scene.Add(go);

						go = std::make_shared<dae::GameObject>();
						go->GetTransform()->SetLocalPosition(560, 820, 0);
						auto pepperdisp = go->AddComponent<dae::PepperDisplayComponent>();
						pepperdisp->SetActorToDisplay(petergo);
						petergo->GetComponent<dae::PepperComponent>()->AddObserver(pepperdisp);
						scene.Add(go);
					}
				}
				case 11: //peterJr
				{
					if (GameInstance::GetInstance().GetGameMode() == GameMode::coop)
					{
						dae::PeterPepperJr peter{ scene,{x.GetFloat(),y.GetFloat()} };
						auto peterjr = peter.GetGameObject();
						peterjr->GetComponent<dae::PeterPepperComponent>()->SetSecondPlayer(petergo);

						auto go = std::make_shared<dae::GameObject>();
						go->GetTransform()->SetLocalPosition(560, 800, 0);
						auto pepperdisp = go->AddComponent<dae::PepperDisplayComponent>();
						pepperdisp->SetActorToDisplay(peterjr);
						peterjr->GetComponent<dae::PepperComponent>()->AddObserver(pepperdisp);
						scene.Add(go);
					}
					break;
				}
				case 12: //playerHotDog
				{
					if (GameInstance::GetInstance().GetGameMode() == GameMode::versus)
					{
						dae::PlayerHotDog{ scene,{x.GetFloat(),y.GetFloat()} };
					}
					break;
				}
				case 13:
				{
					EnemySpawner{ scene,{x.GetFloat(),y.GetFloat()} };
					break;
				}
				}
			}
		}
		GameInstance::GetInstance().SetPlates(plates);
	}
}
