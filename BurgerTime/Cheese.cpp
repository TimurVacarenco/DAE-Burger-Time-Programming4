#include "Cheese.h"
#include "CollisionComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "IngredientComponent.h"
#include "Scene.h"

dae::Cheese::Cheese(dae::Scene& scene, Vector2 loc)
{
	Initialize(scene, loc);
}

void dae::Cheese::Initialize(dae::Scene& scene, Vector2 loc)
{
	std::vector<RenderComponent*> sprites;
	std::vector<CollisionComponent*> cols;
	auto go = std::make_shared<dae::GameObject>();

	//SPRITES
	auto rc = go->AddComponent<dae::RenderComponent>();
	rc->SetTexture("\\Sprites\\Ingredients\\cheese0.png");
	rc->SetDimensions(16, 16);

	sprites.push_back(rc);

	rc = go->AddComponent<dae::RenderComponent>();
	rc->SetTexture("\\Sprites\\Ingredients\\cheese1.png");
	rc->SetDimensions(16, 16);
	rc->SetOffsetX(16);

	sprites.push_back(rc);

	rc = go->AddComponent<dae::RenderComponent>();
	rc->SetTexture("\\Sprites\\Ingredients\\cheese2.png");
	rc->SetDimensions(16, 16);
	rc->SetOffsetX(32);

	sprites.push_back(rc);

	rc = go->AddComponent<dae::RenderComponent>();
	rc->SetTexture("\\Sprites\\Ingredients\\cheese3.png");
	rc->SetDimensions(16, 16);
	rc->SetOffsetX(48);

	sprites.push_back(rc);

	//COLLISION
	auto col = go->AddComponent<CollisionComponent>();
	col->SetSize(16, 14);

	cols.push_back(col);

	col = go->AddComponent<CollisionComponent>();
	col->SetSize(16, 14);
	col->SetOffset(16, 0);

	cols.push_back(col);

	col = go->AddComponent<CollisionComponent>();
	col->SetSize(16, 14);
	col->SetOffset(32, 0);

	cols.push_back(col);

	col = go->AddComponent<CollisionComponent>();
	col->SetSize(16, 14);
	col->SetOffset(48, 0);

	cols.push_back(col);

	auto ingredient = go->AddComponent<IngredientComponent>();
	ingredient->SetCollisions(cols);
	ingredient->SetSprites(sprites);

	go->GetTransform()->SetLocalPosition(loc.x, loc.y + 44, 0);
	go->SetTag(Tag::cheese);
	scene.Add(go, 1);

}