#pragma once
#include "BaseComponent.h"
#include "RenderComponent.h"
#include "EnumClasses.h"
namespace dae {
    class AnimationRenderComponent;
    class CollisionComponent;
    class TransformComponent;

    class PlayerHotDogComponent : public BaseComponent
    {
    public:

        PlayerHotDogComponent(GameObject* owner);
        ~PlayerHotDogComponent() {}
        void Update(float deltaTime) override;
        void FixedUpdate(float) override {}

        void SetState(PlayerHotDogState state);
        void ResetState();

        PlayerHotDogState GetState() const { return m_State; }
        void InitAnimation(AnimationRenderComponent* comp);
        void SetOtherPeter(GameObject* peter) { m_OtherPeter = peter; }

        void Stun();
        void Initialize();
    private:
        void HandleMovement(float deltaTime);
        void HandleAnim(float deltaTime);
        void HandleStun(float deltaTime);
        void CheckPeter();

        float m_MovementSpeed = 80.f;

        TransformComponent* m_Transform = nullptr;

        RenderComponent* m_RenderComp = nullptr;

        CollisionComponent* m_CollisionComp = nullptr;

        PlayerHotDogState m_State = PlayerHotDogState::idle;

        bool m_OnPlatform = false;
        bool m_OnLadder = false;

        float m_StunTime{ 1.5f };
        float m_StunElapsed{};

        GameObject* m_OtherPeter = nullptr;

     

        AnimationRenderComponent* m_Anim{};


        int m_RunLeft{};
        int m_RunRight{};
        int m_Climb{};
        int m_ClimbDown{};
        int m_Stunned{};
        int m_Fall{};
        



    };
}