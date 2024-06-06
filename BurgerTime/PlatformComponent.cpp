#include "PlatformComponent.h"
#include "GameObject.h"
#include <CollisionComponent.h>

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

bool dae::PlatformComponent::IsUnder(Rect other) const
{
	return GetOwner()->GetComponent<CollisionComponent>()->IsUnder(other);
}
