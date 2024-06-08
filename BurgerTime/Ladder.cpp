#include "Ladder.h"

#include "CollisionComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "LadderComponent.h"
#include "Scene.h"
#include "EnumClasses.h"

dae::Ladder::Ladder(dae::Scene& scene, Vector2 loc)
{
	Initialize(scene, loc);
}

void dae::Ladder::Initialize(dae::Scene& scene, Vector2 loc)
{
	auto go = std::make_shared<dae::GameObject>();
	auto rc = go->AddComponent<dae::RenderComponent>();
	rc->SetTexture("\\Sprites\\World\\ladder.png");
	rc->SetDimensions(32, 64);

	auto col = go->AddComponent<CollisionComponent>();
	col->SetSize(32, 64);
	go->GetTransform()->SetLocalPosition(loc.x + 16, loc.y, 0);

	go->AddComponent<LadderComponent>();

	go->SetTag(Tag::ladder);
	scene.Add(go);

}
