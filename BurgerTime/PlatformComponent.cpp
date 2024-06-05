#include "PlatformComponent.h"
#include "GameObject.h"
void dae::PlatformComponent::Update(float deltaTime)
{
}
void dae::PlatformComponent::FixedUpdate(float deltaTime)
{
}
dae::PlatformComponent::PlatformComponent(GameObject* owner)
	:BaseComponent{ owner }
{

}

Vector2 dae::PlatformComponent::GetFloorPos() const
{
	auto pos = GetOwner()->GetTransform()->GetLocalPosition();
	Vector2 floorPos = { pos.x,pos.y - 62 };
	return floorPos;
}