#pragma once
#include <vector>

#include "BaseComponent.h"
#include "RenderComponent.h"
#include "TransformComponent.h"

namespace dae {
    class Scene;
    class CollisionComponent;

    class EnemySpawnComponent : public BaseComponent
    {
    public:
        EnemySpawnComponent(GameObject* owner);
        void Update(float deltaTime) override;
        void FixedUpdate(float) override {}

    private:
        float m_TimePerSpawn{ 10.f },
            m_ELapsedTime{};
        GameObject* m_Peter{};
    };
}
