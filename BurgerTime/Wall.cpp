#include "Wall.h"

#include "CollisionComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "Input.h"
#include "Scene.h"

dae::Wall::Wall(dae::Scene& scene, Vector2 loc)
{
	Initialize(scene, loc);
}

void dae::Wall::Initialize(dae::Scene& scene, Vector2 loc)
{
	auto go = std::make_shared<dae::GameObject>();

	auto col = go->AddComponent<CollisionComponent>();
	col->SetSize(64, 64);
	go->SetTag(Tag::wall);
	go->GetTransform()->SetLocalPosition(loc.x, loc.y, 0);
	scene.Add(go);


}