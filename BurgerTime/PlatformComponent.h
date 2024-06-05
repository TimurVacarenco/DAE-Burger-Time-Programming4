#pragma once
#include "BaseComponent.h"
#include "Structs.h"

namespace dae {
    class PlatformComponent : public BaseComponent
    {
    private:
        void Update(float deltaTime) override;
        void FixedUpdate(float deltaTime) override;
    public:
        PlatformComponent(GameObject* owner);
        Vector2 GetFloorPos() const;
    };
}