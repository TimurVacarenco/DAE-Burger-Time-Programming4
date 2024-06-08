#include "EnemySpawner.h"

#include "EnemySpawnComponent.h"
#include "GameObject.h"
#include "Scene.h"

EnemySpawner::EnemySpawner(dae::Scene& scene, Vector2 loc)
{
	Initialize(scene, loc);
}

void EnemySpawner::Initialize(dae::Scene& scene, Vector2 loc)
{
	auto go = std::make_shared<dae::GameObject>();

	go->AddComponent<dae::EnemySpawnComponent>();

	go->GetTransform()->SetLocalPosition(loc.x, loc.y, 0);

	scene.Add(go);
}
