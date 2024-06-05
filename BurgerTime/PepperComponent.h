#pragma once
#include "BaseComponent.h"
#include "TransformComponent.h"
#include "EnumClasses.h"
#include "SceneManager.h"
#include "CollisionComponent.h"
#include "Scene.h"

namespace dae {
    class AnimationRenderComponent;
    class PepperComponent : public BaseComponent
    {
    public:
        PepperComponent(GameObject* owner);
        void Update(float deltaTime) override;
        void FixedUpdate(float) override {}
        void SetState(CharacterState state) { m_State = state; }
        void InitAnimation(AnimationRenderComponent* comp);
    private:
        void HandleMovement(float deltaTime);
        void HandleCollision(float deltaTime);
        void HandleAnim();
        CharacterState m_State = CharacterState::idle;
        float m_Speed = 80.f;
        float m_LadderSpeed = 100.f;

        AnimationRenderComponent* m_Anim{};

        int m_Idle{},
            m_RunLeft{},
            m_RunRight{},
            m_Climb{},
            m_ClimbDown{};

        bool m_OnPlatform{ false },
            m_OnLadder{ false },
            m_Colliding{ false };
    };
}