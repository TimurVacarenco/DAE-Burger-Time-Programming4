#include "Plate.h"

#include "CollisionComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "IngredientComponent.h"
#include "Input.h"
#include "Scene.h"

dae::Plate::Plate(dae::Scene& scene, Vector2 loc)
{
	Initialize(scene, loc);
}

void dae::Plate::Initialize(dae::Scene& scene, Vector2 loc)
{
	auto go = std::make_shared<dae::GameObject>();

	//SPRITES
	auto rc = go->AddComponent<dae::RenderComponent>();
	rc->SetTexture("\\Sprites\\World\\plate.png");
	rc->SetDimensions(64, 7);


	//COLLISION
	auto col = go->AddComponent<CollisionComponent>();
	col->SetSize(64, 7);

	go->GetTransform()->SetLocalPosition(loc.x, loc.y + 57, 0);
	go->SetTag(Tag::plate);
	scene.Add(go);

}