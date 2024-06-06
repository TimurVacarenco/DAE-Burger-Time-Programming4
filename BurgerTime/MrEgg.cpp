#include "MrEgg.h"
#include <CollisionComponent.h>
#include <AnimationRenderComponent.h>
#include "EnemyComponent.h"
#include "GameObject.h"
#include <Scene.h>


dae::MrEgg::MrEgg(dae::Scene& scene, Vector2 loc, GameObject* peter)
{
	Initialize(scene, loc, peter);
}

void dae::MrEgg::Initialize(dae::Scene& scene, Vector2 loc, GameObject* peter)
{
	auto go = std::make_shared<dae::GameObject>();
	auto enemycomp = go->AddComponent<EnemyComponent>();
	enemycomp->SetPeter(peter);

	auto rc = go->AddComponent<dae::AnimationRenderComponent>();
	rc->SetDimensions(m_Height, m_Width);
	rc->SetSpriteDimensions(16, 16);
	enemycomp->InitAnimation(rc, "\\Sprites\\Enemies\\egg.png");

	auto col = go->AddComponent<CollisionComponent>();
	col->SetSize(32, 32);

	go->SetTag(Tag::egg);

	go->GetTransform()->SetLocalPosition(loc.x + 16, loc.y + 16, 0);
	scene.Add(go, 0);
}
