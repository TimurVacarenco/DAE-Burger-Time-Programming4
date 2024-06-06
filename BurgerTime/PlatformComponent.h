#pragma once
#include "BaseComponent.h"
#include "Structs.h"

namespace dae {
    class PlatformComponent : public BaseComponent
    {
    public:
        PlatformComponent(GameObject* owner);
        Vector2 GetFloorPos() const;
        bool IsUnder(Rect other) const;
    };
}