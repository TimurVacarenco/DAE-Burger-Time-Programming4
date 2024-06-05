#include "Ladder.h"
#include <GameObject.h>
#include <RenderComponent.h>
#include <CollisionComponent.h>
#include <EnumClasses.h>
#include <Scene.h>
dae::Ladder::Ladder(dae::Scene& scene, Vector2 loc)
{
	Initialize(scene, loc);
}

void dae::Ladder::Initialize(dae::Scene& scene, Vector2 loc)
{
	auto go = std::make_shared<dae::GameObject>();
	auto rc = go->AddComponent<dae::RenderComponent>();
	rc->SetTexture("\\Sprites\\World\\ladder.png");
	rc->SetDimensions(64, 64);

	auto col = go->AddComponent<CollisionComponent>();
	col->SetSize(64, 64);
	go->GetTransform()->SetLocalPosition(loc.x, loc.y, 0);

	go->SetTag(Tag::ladder);
	scene.Add(go,2);

}