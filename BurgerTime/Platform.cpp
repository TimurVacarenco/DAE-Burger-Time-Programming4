#include "Platform.h"

#include "CollisionComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "Input.h"
#include "Scene.h"

dae::Platform::Platform(dae::Scene& scene, Vector2 loc)
{
	Initialize(scene, loc);
}

void dae::Platform::Initialize(dae::Scene& scene, Vector2 loc)
{
	auto go = std::make_shared<dae::GameObject>();
	auto rc = go->AddComponent<dae::RenderComponent>();
	rc->SetTexture("\\Sprites\\World\\platform.png");
	rc->SetDimensions(64, 64);

	auto col = go->AddComponent<CollisionComponent>();
	col->SetSize(64, 5);
	col->SetOffset(0, 59);
	go->GetTransform()->SetLocalPosition(loc.x, loc.y, 0);

	go->SetTag(Tag::platform);
	scene.Add(go);

}